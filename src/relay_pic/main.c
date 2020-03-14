#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f1826.h>
#include "timer.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/mcc.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define MAX_LOOP_TIME_DIFF_CONST 100

#define IGNITION_BOARD    1
#define REMOTE_FILL_BOARD 2
#define REMOTE_VENT_BOARD 3
#define LINAC_BOARD       4

uint16_t dipInputs;
uint16_t adcResult;
uint16_t i2cSlaveRecv; // Data received on i2c
uint16_t i2cSlaveSend; // Data to be sent on i2c

void i2cSlaveInit(uint16_t address) {
    SSPSTAT = 0x80;
    SSPADD = address;
    SSPCON = 0x36;
    SSPCON2 = 0x01;
    //TRISB1 = 1; // SDA
    //TRISB4 = 1; // SCL
    GIE = 1;
    PEIE = 1;
    SSP1IF = 0;
    SSP1IE = 1;
}


static void __interrupt() interrupt_handler() {
    if (SSP1IF == 1) {
        uint16_t temp;
        SSPCONbits.CKP = 0;
       
        // If overflow or collision.
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)) {
            temp = SSPBUF; // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0; // Clear the overflow flag
            SSPCONbits.WCOL = 0;   // Clear the collision bit
            SSPCONbits.CKP = 1;
        }

        // If last byte was Address + write
        if (!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            temp = SSPBUF;
            while(!BF);
            i2cSlaveRecv = SSPBUF;
            SSPCONbits.CKP = 1;
            SSPM3 = 0;
       }
        
       // If last byte was Address + read
       else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW) {
           temp = SSPBUF;
           BF = 0;
           SSPBUF = i2cSlaveSend;
           SSPCONbits.CKP = 1;
           while(SSPSTATbits.BF);
       }
       
       SSP1IF = 0;
    } // if
    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        timer0_handle_interrupt();
        INTCONbits.TMR0IF = 0;
    }
}
//void readAnalogInputs() {
//    for (int i = 0; i < 1000; i++) {}
//    ADCON0 = 0x01; // Turn ADC on
//    ADCON0 |= 1 << 1; // set b[1] "go" bit
//    uint8_t doneBit;
//    do { //wait for ADC to complete (go bit switches to 0 automatically when done)
//        doneBit = ADCON0 & (1 << 1);
//    } while (doneBit); //while go bit is on (AD conversion in progress)
//
//    adcResult = (ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value
//
//    ADCON0 = 0x00; //Turn ADC off return;
//}

void setPower(bool out) { 
    if (out) {
        LATAbits.LATA2 = 1;
    } else {
        LATAbits.LATA2 = 0;
    }
}

void setSelect(bool out) {
    if (out) {
        LATAbits.LATA3 = 1;
    } else {
        LATAbits.LATA3 = 1;
    }
}

void setLim1(bool out) {
    if (out) {
        LATAbits.LATA7 = 1;
    } else {
        LATAbits.LATA7 = 0;
    }
}

void setLim2(bool out) {
    if (out) {
        LATAbits.LATA6 = 1;
    } else {
        LATAbits.LATA6 = 1;
    }
}

void setLed(bool out) {
    if (out) {
        LATBbits.LATB5 = 1;
    } else {
        LATBbits.LATB5 = 0;
    }
}

void led_heartbeat(void) {
    static bool led_on = true;
    if (led_on) {
        setLed(0);
        led_on = false;
    } else {
        setLed(1);
        led_on = true;
    }
}

void readDipInputs() {
    uint16_t newDip = 0;
    newDip |= (!PORTBbits.RB3) ? (1) : 0;       //LSB
    newDip |= (!PORTBbits.RB2) ? (1 << 1) : 0;  
    newDip |= (!PORTBbits.RB0) ? (1 << 2) : 0;
    newDip |= (!PORTAbits.RA4) ? (1 << 3) : 0;  //MSB
    dipInputs = newDip;
}

void setup() {
    TRISAbits.TRISA0 = 1;   //CURR_SENSE_2
    TRISAbits.TRISA1 = 1;   //CURR_SENSE_1
    TRISAbits.TRISA2 = 0;   //POWER
    TRISAbits.TRISA3 = 0;   //SELECT
    TRISAbits.TRISA4 = 1;   //DIP_1
    TRISAbits.TRISA6 = 0;   //LIM2
    TRISAbits.TRISA7 = 0;   //LIM1
    TRISBbits.TRISB0 = 1;   //DIP_2
    TRISBbits.TRISB2 = 1;   //DIP_3
    TRISBbits.TRISB3 = 1;   //DIP_4 
    TRISBbits.TRISB5 = 0;   //LED
    
    ANSELA = 0;             //DISABLE ANALOG INPUT ON PORT A, then enable port 0 and 1
    ANSELAbits.ANSA0 = 1;   //CURR_SENSE_2
    ANSELAbits.ANSA1 = 1;   //CURR_SENSE_1
    
    ANSELB = 0;             //DISABLE ANALOG INPUT ON PORT B
    
    // Configure ADC module 
    // b[7] sets right justification, b[6:4] sets CS = FRC,
    // b[2]+b[1:0] sets Vss and Vdd as references.
    ADCON1 = 0b11110000;
}

int main(int argc, char** argv) {
    setup();
    timer0_init();
    readDipInputs();
//    i2cSlaveInit(dipInputs);
    
    uint32_t last_millis = millis();
    setLed(0);
    while (1) {
        //Blink the LED
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_CONST) {
            //One day I will configure this correctly, but ATM we only need the LED to blink ;-;
            //led_heartbeat();
            last_millis = millis();
        }

        readDipInputs(); //4fun
        if(dipInputs == REMOTE_FILL_BOARD) {
            setLed(1);
        } else {
            setLed(0);
        }
        //readAnalogInputs();
    }
    return (EXIT_SUCCESS);
}

