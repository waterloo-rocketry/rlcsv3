#ifndef TIMER_H
#define	TIMER_H

#include <stdint.h>
#include <xc.h>
#include <pic16f1826.h>

// utilities for handling the timer used in millis()
void timer0_init(void);

// should be called from the general ISR to increment the timer
void timer0_handle_interrupt(void);

// Returns milliseconds since the timer was initialized
uint32_t millis(void);

#endif	/* TIMER_H */
