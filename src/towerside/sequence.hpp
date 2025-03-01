#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "common/config.hpp"

namespace sequence {

struct SequenceItem{
  int time;
  const char step[4];
  ActuatorMessage valve_states;
};

void find_state(ActuatorMessage &current_cmd);
void act_on_state(ActuatorMessage &current_cmd);

void update_sensor_message(SensorMessage &msg);

bool apply_sequence(int i);

}


#endif
