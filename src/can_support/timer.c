#include <xc.h>
#include <pic18f26k83.h>

#include "timer.h"

/*
 * Magic numbers: timer is driven on a 500kHz clock and is 8 bits.
 * Timer rolls over every 256 counts, or every 512 microseconds.
 * MILLIS_INCREMENT = 0, since there are 0 ms added each rollover
 * MILLIS_REMAINDER = 512, added each time the timer is triggered
 * MILLIS_INCREMENT_CAP = 1000, number of microseconds before we tick over a millisecond
 *
 * Only the ratio between MILLIS_REMAINDER and MILLIS_INCREMENT_CAP matters, so
 * we can optimize things a little bit by dividing both by 8 so that the largest
 * value of internal_count can fit within 8 bits.
 *
 */
#define MILLIS_INCREMENT 0
#define MILLIS_REMAINDER 64
#define MILLIS_INCREMENT_CAP 125

 static uint32_t millis_counter = 0;

 uint32_t millis(void) {
    return millis_counter;
}

void timer0_init(void) {
    PIE3bits.TMR0IE = 1;    //enable timer 0 interrupt

    T0CON0bits.EN = 0;      // disable timer module
    T0CON0bits.MD16 = 0;    // set up timer as 8 bits

    T0CON0bits.OUTPS = 0;
    T0CON1bits.CKPS = 0;

    T0CON1bits.CS = 0x5;    // drive timer from 500 kHz
    T0CON1bits.ASYNC = 0;

     //enable the module
    T0CON0bits.EN = 1;
}

/*
 * Based on Bresenham's algorithm and described here: http://romanblack.com/one_sec.htm
 */
void timer0_handle_interrupt() {
    static uint8_t internal_count = 0;

    millis_counter += MILLIS_INCREMENT;
    internal_count += MILLIS_REMAINDER;
    if (internal_count > MILLIS_INCREMENT_CAP) {
        internal_count -= MILLIS_INCREMENT_CAP;
        millis_counter++;
    }
}
