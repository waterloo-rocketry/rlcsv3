<<<<<<< HEAD
#include "relay_general.h"

uint16_t readAnalogInputs() {
    uint16_t adc_result = 0;
    for (int i = 0; i < 1000; i++) {}
    ADCON0 = 0x01; // Turn ADC on
=======
#include <xc.h>
#include "relay_general.h"

static uint16_t analog_inputs[2];
uint16_t read_analog_inputs(uint8_t port) {
    ADCON0 = 0x01 | (port << 2); // Turn ADC on, select port to read from
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
    ADCON0 |= 1 << 1; // set b[1] "go" bit
    uint8_t done_bit;
    do { //wait for ADC to complete (go bit switches to 0 automatically when done)
        done_bit = ADCON0 & (1 << 1);
    } while (done_bit); //while go bit is on (AD conversion in progress)

<<<<<<< HEAD
    adc_result = (ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value

    ADCON0 = 0x00; //Turn ADC off return;
    
=======
    uint16_t adc_result = (ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value
    analog_inputs[port] = adc_result;

    ADCON0 = 0x00; //Turn ADC off return;

>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
    return adc_result;
}

void set_power_on(void) {
    set_power(true);
}

void set_power_off(void) {
    set_power(false);
}

void set_select_on(void) {
    set_select(true);
}

void set_select_off(void) {
    set_select(false);
}

<<<<<<< HEAD
void set_lim1_on(void) {
    set_lim1(true);
}

void set_lim1_off(void) {
    set_lim1(false);
}

void set_lim2_on(void) {
    set_lim2(true);
}

void set_lim2_off(void) {
    set_lim2(false);
}

=======
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
void set_led_on(void) {
    set_led(true);
}

void set_led_off(void) {
    set_led(false);
}

<<<<<<< HEAD
void set_power(bool out) { 
=======
void set_power(bool out) {
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
    if (out) {
        LATAbits.LATA2 = 1;
    } else {
        LATAbits.LATA2 = 0;
    }
}

void set_select(bool out) {
    if (out) {
        LATAbits.LATA3 = 1;
    } else {
<<<<<<< HEAD
        LATAbits.LATA3 = 1;
    }
}

void set_lim1(bool out) {
    if (out) {
        LATAbits.LATA7 = 1;
    } else {
        LATAbits.LATA7 = 0;
    }
}

void set_lim2(bool out) {
    if (out) {
        LATAbits.LATA6 = 1;
    } else {
        LATAbits.LATA6 = 1;
=======
        LATAbits.LATA3 = 0;
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
    }
}

void set_led(bool out) {
    if (out) {
        LATBbits.LATB5 = 1;
    } else {
        LATBbits.LATB5 = 0;
    }
}

void led_heartbeat(void) {
    static bool led_on = false;
    if (led_on) {
        set_led_off();
        led_on = false;
    } else {
        set_led_on();
        led_on = true;
    }
}

<<<<<<< HEAD
=======
bool get_lim1(void) {
    return PORTAbits.RA7;
}

bool get_lim2(void) {
    return PORTAbits.RA6;
}
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
