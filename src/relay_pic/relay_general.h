#ifndef RELAY_GENERAL_H
#define RELAY_GENERAL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

uint16_t analog_inputs[2];

uint16_t read_analog_inputs(uint8_t port);

void set_power_on(void);

void set_power_off(void);

void set_select_on(void);

void set_select_off(void);

void set_led_on(void);

void set_led_off(void);

void led_heartbeat(void);

bool get_lim1(void);

bool get_lim2(void);

//internal functions
void set_power(bool out);
void set_select(bool out);
void set_led(bool out);


#endif /* RELAY_GENERAL_H */

