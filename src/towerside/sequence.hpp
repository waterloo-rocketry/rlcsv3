#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "common/config.hpp"

namespace sequence {

enum State {
    MANUAL,
    AUTOMATIC,
    SEQUENCE1,
    SEQUENCE2,
};

void set_state(State &state, ActuatorMessage &current_cmd, unsigned long &start_time);

bool apply_sequence_one(unsigned long delta_time);
bool apply_sequence_two(unsigned long delta_time);

}


#endif