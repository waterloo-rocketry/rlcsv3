#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

namespace hardware {

void setup();
void set_missile_leds(bool value);
void set_status_startup();
void set_status_connected();
void set_status_disconnected();
bool is_armed();
uint8_t get_batt_dv();

} // namespace hardware

#endif
