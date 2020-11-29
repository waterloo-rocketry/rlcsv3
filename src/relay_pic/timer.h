#ifndef TIMER_H
<<<<<<< HEAD
#define	TIMER_H

#include <stdint.h>
#include <xc.h>
#include <pic16f1826.h>
=======
#define TIMER_H

#include <stdint.h>
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

// utilities for handling the timer used in millis()
void timer0_init(void);

// should be called from the general ISR to increment the timer
void timer0_handle_interrupt(void);

// Returns milliseconds since the timer was initialized
uint32_t millis(void);

<<<<<<< HEAD
#endif	/* TIMER_H */
=======
#endif /* TIMER_H */
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
