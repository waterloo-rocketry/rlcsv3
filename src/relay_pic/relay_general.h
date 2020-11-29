#ifndef RELAY_GENERAL_H
<<<<<<< HEAD
#define	RELAY_GENERAL_H
=======
#define RELAY_GENERAL_H
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
<<<<<<< HEAD
#include <xc.h>
#include <pic16f1826.h>

uint16_t readAnalogInputs(void);
=======

uint16_t analog_inputs[2];

uint16_t read_analog_inputs(uint8_t port);
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

void set_power_on(void);

void set_power_off(void);

void set_select_on(void);

void set_select_off(void);

<<<<<<< HEAD
void set_lim1_on(void);

void set_lim1_off(void);

void set_lim2_on(void);

void set_lim2_off(void);

=======
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2
void set_led_on(void);

void set_led_off(void);

void led_heartbeat(void);

<<<<<<< HEAD
//internal functions
void set_power(bool out);
void set_select(bool out);
void set_lim1(bool out);
void set_lim2(bool out);
void set_led(bool out);


#endif	/* RELAY_GENERAL_H */
=======
bool get_lim1(void);

bool get_lim2(void);

//internal functions
void set_power(bool out);
void set_select(bool out);
void set_led(bool out);


#endif /* RELAY_GENERAL_H */
>>>>>>> 4e0c8d71b3290d9faf8db479f6ec01670aabe4c2

