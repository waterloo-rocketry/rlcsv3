#include "relay_general.h"

uint16_t readAnalogInputs() {
    uint16_t adc_result = 0;
    for (int i = 0; i < 1000; i++) {}
    ADCON0 = 0x01; // Turn ADC on
    ADCON0 |= 1 << 1; // set b[1] "go" bit
    uint8_t done_bit;
    do { //wait for ADC to complete (go bit switches to 0 automatically when done)
        done_bit = ADCON0 & (1 << 1);
    } while (done_bit); //while go bit is on (AD conversion in progress)

    adc_result = (ADRESH << 8) | ADRESL; //combine two 8bit values into a 16bit value

    ADCON0 = 0x00; //Turn ADC off return;
    
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

