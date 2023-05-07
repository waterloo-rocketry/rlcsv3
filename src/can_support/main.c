#include <xc.h>
#include "i2c.h"

#include "system_init.h"

#define _XTAL_FREQ 12000000;

uint8_t dip_inputs;

void read_dip_inputs(void) {
    uint8_t new_dip = 0;
    new_dip |= (!PORTBbits.RB1) ? (1) : 0;       //LSB
    new_dip |= (!PORTBbits.RB2) ? (1 << 1) : 0;
    new_dip |= (!PORTBbits.RB3) ? (1 << 2) : 0;
    new_dip |= (!PORTBbits.RB4) ? (1 << 3) : 0;  //MSB
    if(dip_inputs != new_dip) {
        dip_inputs = new_dip;
        i2c_set_address(dip_inputs);
    }
}

void main(void) {
    SYSTEM_Initialize(); // calls oscillator init, pin manager init and PMD init

    // C2 is the contol pin for the power relay
    LATC2 = 0;
    TRISC2 = 0;
    
    dip_inputs = 0;
    i2c_set_address(dip_inputs); // Set a "default" address
    read_dip_inputs(); // Read the DIP inputs to set the correct address
    i2c_initialize();
    
    // Enable global interrupts
    INTCON0bits.GIE = 1;
    
    while (1) {
        read_dip_inputs(); // Update if our address changes
    }
}

static void __interrupt() interrupt_handler() {
    if (PIR3bits.I2C1IF == 1 || PIR3bits.I2C1TXIF == 1) {
        i2c_handle_interrupt();
    }
}

