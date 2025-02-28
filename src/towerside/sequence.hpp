#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "common/config.hpp"

namespace sequence {

enum sequence::State get_state();
void set_state(enum sequence::State s);

void find_state(ActuatorMessage &current_cmd);

bool apply_sequence(int i);

}


#endif
