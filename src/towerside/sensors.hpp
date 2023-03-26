#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

namespace sensors {

void setup();

uint16_t get_main_batt_mv();
uint16_t get_actuator_batt_mv();

bool is_armed();
bool has_contact();
void set_contact(bool value);

} // namespace sensors

#endif
