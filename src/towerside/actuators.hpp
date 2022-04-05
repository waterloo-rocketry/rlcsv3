#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>
#include "common/shared_types.hpp"

class Actuator {
  public:
    virtual bool health_check() = 0; // Check whether the actuator is healthy, whatever that means
    virtual void set(bool value) = 0; // Set the state of the actuator
    virtual ActuatorPosition get_position() = 0; // Read the limit switches
    virtual uint16_t get_primary_current() = 0; // Get the actuation currents
    virtual uint16_t get_secondary_current() = 0;
};

class I2CActuator: public Actuator {
  uint8_t slave_address;
  bool current_state = false;
  public:
    I2CActuator(uint8_t slave_address): slave_address{slave_address} {}
    bool health_check() override {
      return true;
    }
    void set(bool value) override {
      current_state = value;
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_primary_current() override {
      return slave_address;
      return 65535;
    }
    uint16_t get_secondary_current() override {
      return 65535;
    }
};


class RocketRadioActuator: public Actuator {
  uint8_t actuator_id;
  bool current_state = false;
  public:
    RocketRadioActuator(uint8_t actuator_id): actuator_id{actuator_id} {}
    bool health_check() override {
      return true;
    }
    void set(bool value) override {
      current_state = value;
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_primary_current() override {
      return actuator_id;
      return 65535;
    }
    uint16_t get_secondary_current() override {
      return 65535;
    }
};

#endif
