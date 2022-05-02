#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"

namespace Actuator {

class Actuator {
  public:
    virtual bool health_check() = 0; // Check whether the actuator is healthy, whatever that means
    virtual void set(bool value) = 0; // Set the state of the actuator
    virtual ActuatorPosition get_position() = 0; // Read the limit switches
    virtual uint16_t get_current(uint8_t index) = 0; // Get the actuation currents
};

class I2C: public Actuator {
  protected: // TODO: get rid of OldI2C and make these private
    uint8_t slave_address;
    bool healthy = true;
  public:
    I2C(uint8_t slave_address): slave_address{slave_address} {}
    bool health_check() override {
      return healthy;
    }
    void set(bool value) override {
      Wire.beginTransmission(slave_address);
      healthy = true;
      // LSB is power, next bit is select.
      healthy &= Wire.write((value << 1) | 1) == 1;
      healthy &= Wire.endTransmission() == 0;
      healthy &= !Wire.getWireTimeoutFlag();
      Wire.clearWireTimeoutFlag();
    }
    ActuatorPosition get_position() override {
      // Cast to uint8_t to avoid warning about ambiguous overload
      healthy = Wire.requestFrom(slave_address, static_cast<uint8_t>(1)) == 1;
      if (!healthy) {
        return ActuatorPosition::error;
      }
      uint8_t lims = Wire.read();
      if (lims == 0) return ActuatorPosition::unknown;
      if (lims == 1) return ActuatorPosition::open;
      if (lims == 2) return ActuatorPosition::closed;
      return ActuatorPosition::error;
    }
    uint16_t get_current(uint8_t index) override {
      if (index > 1) {
        return SENSOR_ERR_VAL;
      }
      // Cast to uint8_t to avoid warning about ambiguous overload
      healthy = Wire.requestFrom(slave_address, static_cast<uint8_t>(5)) == 5;
      if (!healthy) {
        return SENSOR_ERR_VAL;
      }
      Wire.read(); // limit switch values, ignore
      if (index == 1) {
        Wire.read(); Wire.read(); // ignore the first (primary) current value;
      }
      uint16_t adcl = Wire.read();
      uint16_t adch = Wire.read();
      return ((adch << 8) | adcl) * 2; // scaling factor of 2
    }
};

// Actuator that uses the old I2C protocol (to be compatible with the old towerside relay board code)
class OldI2C: public I2C {
  public:
    OldI2C(uint8_t slave_address): I2C(slave_address) {}
    void set(bool value) override {
      healthy = true;
      Wire.beginTransmission(slave_address);
      // LSB is 0 for power, 1 for select, next bit is value
      healthy &= Wire.write((1 << 1) | 0) == 1;
      healthy &= Wire.endTransmission() == 0;
      healthy &= !Wire.getWireTimeoutFlag();
      Wire.beginTransmission(slave_address);
      healthy &= Wire.write((value << 1) | 1) == 1;
      healthy &= Wire.endTransmission() == 0;
      healthy &= !Wire.getWireTimeoutFlag();
      Wire.clearWireTimeoutFlag();
    }
};


class RocketRadio: public Actuator {
  uint8_t actuator_id;
  public:
    RocketRadio(uint8_t actuator_id): actuator_id{actuator_id} {}
    bool health_check() override {
      return true;
    }
    void set(bool value) override {
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_current(uint8_t index) override {
      return SENSOR_ERR_VAL;
      return actuator_id;
    }
};

}

#endif
