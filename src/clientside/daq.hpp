#ifndef DAQ_H
#define DAQ_H

#include "common/shared_types.hpp"

namespace DAQ {

ActuatorCommand get_switch_positions();

uint8_t get_batt_dv(); // get clientside battery in 10ths of a volt for displaying

}

#endif
