#include <xc.h>
#include "relay_general.h"

uint16_t curr_sense_1 = 0;
uint16_t curr_sense_2 = 0;
uint16_t read_analog_inputs(uint8_t port) {
    ADCON0 = 0x01 | (port << 2); // Turn ADC on, select port to read from
    ADCON0 |= 1 << 1; // set b[1] "go" bit
    uint8_t done_bit;
    do { //wait for ADC to complete (go bit switches to 0 automatically when done)
        done_bit = ADCON0 & (1 << 1);
    } while (done_bit); //while go bit is on (AD conversion in progress)

    uint16_t adc_result = ((uint16_t)ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value
    if (port == CURR_SENSE_1) {
        curr_sense_1 = adc_result;
    } else {
        curr_sense_2 = adc_result;
    }

    ADCON0 = 0x00; //Turn ADC off return;

    return adc_result;
}

uint16_t get_analog_inputs(uint8_t port) {
    if (port == CURR_SENSE_1) {
        return curr_sense_1;
    } else {
        return curr_sense_2;
    }
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

void set_led_on(void) {
    set_led(true);
}

void set_led_off(void) {
    set_led(false);
}

void set_power(bool out) {
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
        LATAbits.LATA3 = 0;
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

bool get_lim1(void) {
    return PORTAbits.RA7;
}

bool get_lim2(void) {
    return PORTAbits.RA6;
}
