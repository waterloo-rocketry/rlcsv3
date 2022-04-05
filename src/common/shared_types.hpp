#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <stdint.h>
#include "config.hpp"

#define VERSION 1

enum class ActuatorPosition {
  // Ordered this way so that position = open_lim + 2 * close_lim
  unknown = 0,
  open = 1,
  closed = 2,
  error = 3
};

/*
class ActuatorState {
  uint8_t actuator_states[NUM_ACTUATORS];
  ActuatorState(uint8_t acuator_states[NUM_ACTUATORS]) {
    for (int i = 0; i < NUM_ACTUATORS; i++)
      this->actuator_states[i] = actuator_states[i];
  }

  bool get_state(uint8_t actuator) {
    if (actuator >= NUM_ACTUATORS)
      return 0;
    return actuator_states[actuator];
  }

  void set_state(uint8_t actuator, bool value) {
    if (actuator >= NUM_ACTUATORS)
      return;
    actuator_states[actuator] = value;
  }
};*/

#endif
