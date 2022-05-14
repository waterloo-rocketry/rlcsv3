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
  uint8_t slave_address; // slave address we are controlling
  bool healthy = true; // was the last communication with the slave successful
  virtual bool get_power(bool value) {
    return true;
  }
  virtual bool get_select(bool value) {
    return !value; // Valves are wired up such that select being off means the valve is open
  }
  public:
    I2C(uint8_t slave_address):
      slave_address{slave_address} {}
    bool health_check() override {
      return healthy;
    }
    void set(bool value) override {
      healthy = true;
      Wire.beginTransmission(slave_address);
      // Relay boards have two relays. One turns on power, and the other selects which direction to apply power to.
      // LSB is power, next bit is select.
      bool power = get_power(value);
      bool select = get_select(value);
      healthy &= Wire.write((select << 1) | power) == 1; // returns the number of bytes written, should be 1
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
      Serial.print(Wire.read()); Serial.print(" "); // limit switch values, ignore
      if (index == 1) { // if we want the secondary current
      Serial.print(Wire.read()); Serial.print(" "); // limit switch values, ignore
      Serial.print(Wire.read()); Serial.print(" "); // limit switch values, ignore
      //  Wire.read(); Wire.read(); // ignore the first (primary) current value (2 bytes)
      }
      uint16_t adcl = Wire.read(); // get the 16-bit current reading
      uint16_t adch = Wire.read();
      Serial.print(adcl); Serial.print(" "); Serial.print(adch); Serial.print(" ");
      if (index == 0) {
        Serial.print(Wire.read()); Serial.print(" "); // limit switch values, ignore
        Serial.print(Wire.read()); Serial.print(" "); // limit switch values, ignore
      }
      Serial.println();
      return ((adch << 8) | adcl) * 5; // intervals of 2mV, 20V/V scaling, 0.02R sense
    }
};

class Ignition: public I2C {
  bool primary_on;
  bool secondary_on;
  void set_primary(bool value) { primary_on = value; }
  void set_secondary(bool value) { secondary_on = value; set(false); } // actually trigger the I2C parent
  bool get_power(bool) override {
    return primary_on != secondary_on; // turn on power if exactly one of primary and secondary are set
  }
  bool get_select(bool) override {
    return secondary_on && !primary_on; // only set select if secondary is on and primary is off
  }
  public:
    Ignition(uint8_t slave_address): I2C(slave_address) {}
    class Primary: public Actuator {
      Ignition *ignition;
      Primary(Ignition *ignition): ignition{ignition} {}

      public:
        bool health_check() { return ignition->health_check(); }
        void set(bool value) { ignition->set_primary(value); }
        ActuatorPosition get_position() { return ignition->get_position(); }
        uint16_t get_current(uint8_t index) { return ignition->get_current(0); }
      friend class Ignition;
    };
    class Secondary: public Actuator {
      Ignition *ignition;
      Secondary(Ignition *ignition): ignition{ignition} {}

      public:
        bool health_check() { return ignition->health_check(); }
        void set(bool value) { ignition->set_secondary(value); }
        ActuatorPosition get_position() { return ignition->get_position(); }
        uint16_t get_current(uint8_t index) { return ignition->get_current(1); }
      friend class Ignition;
    };
    Primary *primary_actuator() { return new Primary{this}; }
    Secondary *secondary_actuator() { return new Secondary{this}; }
  
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
