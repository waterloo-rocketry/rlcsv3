#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include "common/shared_types.hpp"
#include "common/mock_arduino.hpp"
#include "common/tickable.hpp"
#include "actuators.hpp"

namespace Sensor {

class Sensor {
  public:
    virtual uint16_t get_value() = 0; // Return the value of the sensor, always a uint16_t for simplicity
};

// Get the position of an actuator (since the actuator interface exposes get_position)
class ActuatorPosition: public Sensor {
  Actuator::Actuator *actuator;
  public:
    ActuatorPosition(Actuator::Actuator *actuator): actuator{actuator} {}
    uint16_t get_value() override {
      return static_cast<uint16_t>(actuator->get_position());
    }
};

// Get the primary or secondary current of an actuator
class ActuatorCurrent: public Sensor {
  Actuator::Actuator *actuator;
  uint8_t index;
  public:
    ActuatorCurrent(Actuator::Actuator *actuator, uint8_t index): actuator{actuator}, index{index} {}
    uint16_t get_value() override {
      return actuator->get_current(index);
    }
};

// Count the number of healthy actuators
class HealthyActuators: public Sensor {
  Actuator::Actuator *(&actuators)[NUM_ACTUATORS];
  public:
    HealthyActuators(Actuator::Actuator *(&actuators)[NUM_ACTUATORS]): actuators{actuators} {}
    uint16_t get_value() override {
      uint16_t count = 0;
      for (uint8_t i = 0; i < NUM_ACTUATORS; i++) {
        if (actuators[i]->health_check()) {
          count++;
        }
      }
      return count;
    }
};

// Read an analog input pin. Uses a moving average and also applies a linear calibration (mx + b) to the value
class Analog: public Sensor, Tickable {
  uint8_t pin;
  uint16_t m_num;
  uint16_t m_den;
  uint16_t b;
  uint8_t rolling_avg_width;
  uint16_t *rolling_avg;
  uint8_t rolling_avg_index = 0;
  uint16_t rolling_sum = 0; // keep a rolling sum so we don't need to sum over the list whenever the value is requested
  public:
    // Allow specifying numerator and denomincator of slope separately
    // to avoid loss in precision and floating point math.
    Analog(uint8_t pin, uint16_t m_num, uint16_t m_den, uint16_t b, uint8_t rolling_avg_width=16):
        pin{pin}, m_num{m_num}, m_den{m_den}, b{b}, rolling_avg_width{rolling_avg_width},
        rolling_avg{new uint16_t[rolling_avg_width]} {
      for (uint8_t i = 0; i < rolling_avg_width; i++) {
        rolling_avg[i] = 0;
      }
      pinMode(pin, INPUT);
      digitalWrite(pin, false); // turn off any pullup
    }
    uint16_t get_value() override {
      // analog input values are in multiples of ~5 mV (technically 5/1024), so multiply by 5
      uint16_t avg = rolling_sum / rolling_avg_width;
      return avg * m_num / m_den * 5 + b;
    }
    void tick() override {
      rolling_avg_index += 1;
      if (rolling_avg_index >= rolling_avg_width) {
        rolling_avg_index = 0;
      }
      // analog read values are at most 2^10 so we can safely add 2^6 of them without overflowing.
      rolling_sum -= rolling_avg[rolling_avg_index];
      rolling_avg[rolling_avg_index] = analogRead(pin);
      rolling_sum += rolling_avg[rolling_avg_index];
    }
};

class TowersideState: public Sensor {
  uint8_t disarm_pin;
  bool has_contact = false;
  public:
    TowersideState(uint8_t disarm_pin): disarm_pin{disarm_pin} {}
    uint16_t get_value() override {
      bool disarmed = digitalRead(disarm_pin);
      return disarmed * 10 + (!has_contact);
    }
    void set_contact(bool value) {
      has_contact = value;
    }
};

}

#endif
