#include <stdint.h>
#include <stdlib.h>
#include <xc.h>
#include "i2c.h"
#include "relay_general.h"
#include "timer.h"

#define MAX_LOOP_TIME_DIFF_CONST 100

#define CURR_SENSE_1 1
#define CURR_SENSE_2 0

uint16_t dip_inputs;

static void __interrupt() interrupt_handler(void) {
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

void read_dip_inputs(void) {
    uint16_t new_dip = 0;
    new_dip |= (!PORTBbits.RB3) ? (1) : 0;       //LSB
    new_dip |= (!PORTBbits.RB2) ? (1 << 1) : 0;
    new_dip |= (!PORTBbits.RB0) ? (1 << 2) : 0;
    new_dip |= (!PORTAbits.RA4) ? (1 << 3) : 0;  //MSB
    if(dip_inputs != new_dip) {
        dip_inputs = new_dip;
        i2c_slave_init(dip_inputs); //reinitialize i2c slave module with new slave address
    }
}

void setup(void) {
    TRISAbits.TRISA0 = 1;   //CURR_SENSE_2
    TRISAbits.TRISA1 = 1;   //CURR_SENSE_1
    TRISAbits.TRISA2 = 0;   //POWER
    TRISAbits.TRISA3 = 0;   //SELECT
    TRISAbits.TRISA4 = 1;   //DIP_1
    TRISAbits.TRISA6 = 1;   //LIM2
    TRISAbits.TRISA7 = 1;   //LIM1
    TRISBbits.TRISB0 = 1;   //DIP_2
    TRISBbits.TRISB2 = 1;   //DIP_3
    TRISBbits.TRISB3 = 1;   //DIP_4
    TRISBbits.TRISB5 = 0;   //LED

    ANSELA = 0;             //DISABLE ANALOG INPUT ON PORT A, then enable port 0 and 1
    ANSELAbits.ANSA0 = 1;   //CURR_SENSE_2
    ANSELAbits.ANSA1 = 1;   //CURR_SENSE_1

    ANSELB = 0;             //DISABLE ANALOG INPUT ON PORT B

    // Configure FVR module
    // b[7] enables FVR
    // b[1:0] sets the reference to 4.096
    FVRCON = 0b10000011;

    // Configure ADC module
    // b[7] sets right justification, b[6:4] sets CS = FRC,
    // b[2]+b[1:0] sets Vss and FVR as references.
    ADCON1 = 0b11110011;
}

int main(int argc, char** argv) {
    setup();                    //Set up digital + analog I/O
    timer0_init();              //Initialize timer
    set_power_on();
    set_select_off();
    set_led_off();
    dip_inputs = 0;
    i2c_slave_init(dip_inputs);
    read_dip_inputs();            //Get actual dip switch value to set slave address, init i2c

    uint32_t last_millis = millis();

    while (1) {
        //Heartbeat
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_CONST) {
            //One day I will configure this correctly, but ATM we only need the LED to blink ;-;
            last_millis = millis();

            led_heartbeat();
        }

        read_analog_inputs(CURR_SENSE_1);
        read_analog_inputs(CURR_SENSE_2);

        read_dip_inputs(); //Check if dip switch input has changed, re-init i2c if so
    }
    return (EXIT_SUCCESS);
}

