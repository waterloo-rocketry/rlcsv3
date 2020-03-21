#ifndef RELAY_GENERAL_H
#define	RELAY_GENERAL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f1826.h>

uint16_t readAnalogInputs(void);

void set_power_on(void);

void set_power_off(void);

void set_select_on(void);

void set_select_off(void);

void set_lim1_on(void);

void set_lim1_off(void);

void set_lim2_on(void);

void set_lim2_off(void);

void set_led_on(void);

void set_led_off(void);

void led_heartbeat(void);

//internal functions
void set_power(bool out);
void set_select(bool out);
void set_lim1(bool out);
void set_lim2(bool out);
void set_led(bool out);


#endif	/* RELAY_GENERAL_H */

