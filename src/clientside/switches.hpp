#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stdint.h>
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"

namespace Switch {

class Switch {
  public:
    virtual bool is_pressed() = 0;
};

class Missile: public Switch {
  uint8_t pin;
  public:
    Missile(uint8_t pin): pin{pin} {
      pinMode(pin, INPUT);
    }
    bool is_pressed() override {
      return digitalRead(pin);
    }
};

class Ignition: public Switch {
  // Requires pin_a and _b to be pressed, and *not* pin_invert.
  uint8_t pin_a;
  uint8_t pin_b;
  uint8_t pin_invert;
  public:
    Ignition(uint8_t pin_a, uint8_t pin_b, uint8_t pin_invert):
        pin_a{pin_a}, pin_b{pin_b}, pin_invert{pin_invert} {
      pinMode(pin_a, INPUT);
    }
    bool is_pressed() override {
      return digitalRead(pin_a) && digitalRead(pin_b) && !digitalRead(pin_invert);
    }
};

}

#endif
