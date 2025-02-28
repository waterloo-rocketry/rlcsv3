#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "common/config.hpp"

namespace sequence {

void set_state(State &state, ActuatorMessage &current_cmd, unsigned long &start_time);

bool apply_sequence(int i, unsigned long delta_time);

}


#endif
