#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include "common/shared_types.hpp"

class Sensor {
  public:
    virtual uint16_t get_value() = 0;
};

class I2CLimitSwitchSensor: public Sensor {
  public:
    uint16_t get_value() override {
      return static_cast<uint16_t>(ActuatorPosition::unknown);
    }
};

class I2CCurrentSensor: public Sensor {
  public:
    uint16_t get_value() override {
      return static_cast<uint16_t>(ActuatorPosition::unknown);
    }
};

class AnalogSensor: public Sensor {
  public:
    uint16_t get_value() override {
      return 0;
    }
};

#endif
