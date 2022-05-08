#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"

namespace Actuator {

// Abstract actuator interface
class Actuator {
  public:
    virtual bool health_check() = 0; // Check whether the actuator is healthy, whatever that means
    virtual void set(bool value) = 0; // Set the state of the actuator
    virtual ActuatorPosition get_position() = 0; // Read the limit switches
    virtual uint16_t get_current(uint8_t index) = 0; // Get the actuation currents. Index is 0 for primary, 1 for secondary.
};

// I2C relay board actuator
class I2C: public Actuator {
  protected: // TODO: get rid of OldI2C and make these private
    uint8_t slave_address; // slave address we are controlling
    bool active_off; // whether power should be set when select is 0
    bool healthy = true; // was the last communication with the slave successful
  public:
    // active_off determines whether we turn on power when select is off
    // This is necessary because comp requires that at least two components must fail in order for ignition to
    // happen inadvertently. This means we must use two relay boards with the two ignition channels each wired to
    // the 'on' set of each board, so that if the power relay fails we don't trigger an ignition coil connected to the
    // 'off' position.
    I2C(uint8_t slave_address, bool active_off = true):
      slave_address{slave_address}, active_off{active_off} {}
    bool health_check() override {
      return healthy;
    }
    void set(bool value) override {
      healthy = true;
      Wire.beginTransmission(slave_address);
      // Relay boards have two relays. One turns on power, and the other selects which direction to apply power to.
      // LSB is power, next bit is select.
      // TODO: active_off is ugly, come up with a better abstraction between ActuatorCommand bits and power/select
      bool select = value || active_off;
      healthy &= Wire.write((value << 1) | select) == 1; // returns the number of bytes written, should be 1
      healthy &= Wire.endTransmission() == 0; // returns non-zero value if there was an error
      healthy &= !Wire.getWireTimeoutFlag(); // make sure timeout flag is not set
      Wire.clearWireTimeoutFlag(); // if the flag was set, clear it for next time
    }
    ActuatorPosition get_position() override {
      // Cast to uint8_t to avoid warning about ambiguous overload
      healthy = Wire.requestFrom(slave_address, static_cast<uint8_t>(1)) == 1; // returns number of bytes receieved
      if (!healthy) {
        return ActuatorPosition::error;
      }
      uint8_t lims = Wire.read(); // first byte returned is the limit switch values
      if (lims == 0) return ActuatorPosition::unknown;
      if (lims == 1) return ActuatorPosition::open;
      if (lims == 2) return ActuatorPosition::closed;
      return ActuatorPosition::error;
    }
    uint16_t get_current(uint8_t index) override {
      if (index > 1) { // Index must be 0 or 1 for primary or secondary
        return SENSOR_ERR_VAL;
      }
      // Cast to uint8_t to avoid warning about ambiguous overload
      healthy = Wire.requestFrom(slave_address, static_cast<uint8_t>(5)) == 5; // returns number of bytes received
      if (!healthy) {
        return SENSOR_ERR_VAL;
      }
      Wire.read(); // limit switch values, ignore
      if (index == 1) { // if we want the secondary current
        Wire.read(); Wire.read(); // ignore the first (primary) current value (2 bytes)
      }
      uint16_t adcl = Wire.read(); // get the 16-bit current reading
      uint16_t adch = Wire.read();
      return ((adch << 8) | adcl) * 2; // the current is reported in multiples of 2 mA, scale it.
    }
};

// Actuator that uses the old I2C protocol (to be compatible with the old towerside relay board code)
class OldI2C: public I2C {
  public:
    OldI2C(uint8_t slave_address): I2C(slave_address) {}
    void set(bool value) override {
      healthy = true;
      Wire.beginTransmission(slave_address);
      // The old I2C protocol only sets either power or select at a time.
      // LSB is 0 for power, 1 for select. The next bit is the value.
      bool select = value || active_off;
      healthy &= Wire.write((select << 1) | 0) == 1;
      healthy &= Wire.endTransmission() == 0;
      healthy &= !Wire.getWireTimeoutFlag();
      Wire.beginTransmission(slave_address);
      healthy &= Wire.write((value << 1) | 1) == 1;
      healthy &= Wire.endTransmission() == 0;
      healthy &= !Wire.getWireTimeoutFlag();
      Wire.clearWireTimeoutFlag();
    }
};


// TODO: Support for talking to actuator boards over live telemetry
/*
class RocketRadio: public Actuator {
  uint8_t actuator_id;
  public:
    RocketRadio(uint8_t actuator_id): actuator_id{actuator_id} {}
    bool health_check() override {
      return false;
    }
    void set(bool value) override {
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_current(uint8_t index) override {
      return SENSOR_ERR_VAL;
    }
};*/

}

#endif
