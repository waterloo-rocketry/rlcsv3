#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <stdint.h>
#include "config.hpp"
#include "communicator.hpp"
#include "debug.hpp"

#define VERSION 1

enum class ActuatorPosition {
  // Ordered this way so that position = open_lim + 2 * close_lim
  unknown = 0,
  open = 1,
  closed = 2,
  error = 3
};

class ActuatorCommand: Serializable {
  const static uint8_t SIZE = (NUM_ACTUATORS + 7) / 8;
  uint8_t actuator_states[SIZE]; // pack the actuators in a bit field
  public:
    ActuatorCommand() {}
    void set_actuator(ActuatorID::ActuatorID id, bool value) {
      uint8_t i = id / 8;
      uint8_t bit = 1 << (id % 8);
      if (value) {
        actuator_states[i] |= bit;
      } else {
        actuator_states[i] &= ~bit; // bitwise not
      }
    }
    bool get_actuator(ActuatorID::ActuatorID id) {
      uint8_t i = id / 8;
      uint8_t bit = 1 << (id % 8);
      return actuator_states[i] | bit;
    }
    bool operator==(const ActuatorCommand &other) {
      for (int i = 0; i < SIZE; i++) {
        if (actuator_states[i] != other.actuator_states[i]) {
          return false;
        }
      }
      return true;
    }

    static const uint8_t DATA_LENGTH = SIZE;
    bool decode(const uint8_t *buf) override {
      for (int i = 0; i < SIZE; i++) {
        actuator_states[i] = buf[i];
      }
      return true;
    }
    bool encode(uint8_t *buf) override {
      for (int i = 0; i < SIZE; i++) {
        buf[i] = actuator_states[i];
      }
      return true;
    }
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
