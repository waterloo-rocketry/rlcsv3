#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f1826.h>
#include "i2c.h"
#include "relay_general.h"
#include "timer.h"


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define MAX_LOOP_TIME_DIFF_CONST 100

#define IGNITION_BOARD    1
#define REMOTE_FILL_BOARD 2
#define REMOTE_VENT_BOARD 3
#define LINAC_BOARD       4

uint16_t dipInputs;

static void __interrupt() interrupt_handler() {
    //We received a i2c request from master, handle it.
    if (SSP1IF == 1) {
       i2c_handle_interrupt();
    }
    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        timer0_handle_interrupt();
        INTCONbits.TMR0IF = 0;
    }
}

void readDipInputs() {
    uint16_t newDip = 0;
    newDip |= (!PORTBbits.RB3) ? (1) : 0;       //LSB
    newDip |= (!PORTBbits.RB2) ? (1 << 1) : 0;  
    newDip |= (!PORTBbits.RB0) ? (1 << 2) : 0;
    newDip |= (!PORTAbits.RA4) ? (1 << 3) : 0;  //MSB
    if(dipInputs != newDip) {
        dipInputs = newDip;
        i2c_slave_init(dipInputs); //reinitialize i2c slave module with new slave address
    }
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
    setup();                    //Set up digital + analog I/O
    timer0_init();              //Initialize timer
    set_power_off();
    set_power_off();
    set_select_off();
    set_lim1_off();
    set_lim2_off();
    readDipInputs();            //Get dip switch value to set slave address
    i2c_slave_init(dipInputs);  //Set board as i2c slave with dipswitch address
    
    uint32_t last_millis = millis();
    set_led_off();
    while (1) {
        //Heartbeat
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_CONST) {
            //One day I will configure this correctly, but ATM we only need the LED to blink ;-;
            //led_heartbeat();
            last_millis = millis();
        }

        readDipInputs(); //Check if dip switch input has changed
        
        //Some test code to be removed later
        if(dipInputs == REMOTE_FILL_BOARD) {
            set_led_on();
        } else {
            set_led_off();
        }
        
        uint16_t curr = readAnalogInputs();
    }
    return (EXIT_SUCCESS);
}

