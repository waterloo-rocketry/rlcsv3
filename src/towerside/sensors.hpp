#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

namespace sensors {

uint16_t get_main_batt_mv();
uint16_t get_actuator_batt_mv();
uint16_t get_towerside_state();

} // namespace sensors

#endif
