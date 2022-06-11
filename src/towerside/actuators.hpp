#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"
#include "common/communication/can.hpp"
#include "common/communication/sender.hpp"

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
    // unit is centiamp
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
      return ((adch << 8) | adcl) * 10; // adc / 1024 (10bit) * 4096mV (vref) / 4mohm / 100 adc scaler * 1000 mV/V
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

class RocketRadio: public Actuator {
  bool healthy = false;
  public:
    bool health_check() override {
      return healthy;
    }
    void set_healthy(bool val) {
      healthy = val;
    }
    virtual const Communication::CANMessage *build_message() = 0;
};

class BooleanRadio: public RocketRadio {
  Communication::CANMessage *on;
  Communication::CANMessage *off;
  bool state = false;
  public:
    BooleanRadio(Communication::CANMessage *on, Communication::CANMessage *off):
      on{on}, off{off} {}
    void set(bool value) override {
      state = value;
    }
    const Communication::CANMessage *build_message() override {
      if (state) {
        return on;
      } else {
        return off;
      }
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_current(uint8_t index) override {
      return SENSOR_ERR_VAL;
    }
};

class RocketActuator: public BooleanRadio {
  public:
    RocketActuator(uint8_t actuator_id, bool invert = false): BooleanRadio(
      new Communication::CANMessage(0x0C0, 0, 0, 0, actuator_id, invert ? 1 : 0),
      new Communication::CANMessage(0x0C0, 0, 0, 0, actuator_id, invert ? 0 : 1)) {}
};

class RemoteArming: public RocketRadio {
  Communication::CANMessage disarm1 {0x140, 0, 0, 0, 0x01};
  Communication::CANMessage disarm2 {0x140, 0, 0, 0, 0x02};
  Communication::CANMessage arm1 {0x140, 0, 0, 0, 0x11};
  Communication::CANMessage arm2 {0x140, 0, 0, 0, 0x12};
  bool disarming;
  bool state = false;
  bool alternate = false;
  public:
    RemoteArming(bool disarming): disarming{disarming} {}
    void set(bool value) override {
      state = value;
    }
    const Communication::CANMessage *build_message() override {
      if (state) {
        alternate = !alternate;
        if (disarming) {
          return alternate ? &disarm1 : &disarm2;
        } else {
          return alternate ? &arm1 : &arm2;
        }
      }
      return nullptr;
    }
    ActuatorPosition get_position() override {
      return ActuatorPosition::unknown;
    }
    uint16_t get_current(uint8_t index) override {
      return SENSOR_ERR_VAL;
    }
};

}

#endif
