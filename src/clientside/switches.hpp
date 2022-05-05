#ifndef SWITCHES_H
#define SWITCHES_H

#include <stdint.h>
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"

namespace Switch {

class Switch {
  public:
    virtual bool is_pressed() const = 0;
};

class Missile: public Switch {
  uint8_t pin;
  bool invert;
  public:
    Missile(uint8_t pin, bool invert = false): pin{pin}, invert{invert} {
      if (invert) {
        pinMode(pin, INPUT_PULLUP);
      } else {
        pinMode(pin, INPUT);
      }
    }
    bool is_pressed() const override {
      return invert != digitalRead(pin); // != acts as XOR
    }
};

class Ignition: public Switch {
  // Requires switch_a and switch_b to be pressed, and *not* switch_invert.
  const Switch &switch_a;
  const Switch &switch_b;
  const Switch &switch_invert;
  public:
    Ignition(const Switch &switch_a, const Switch &switch_b, const Switch &switch_invert):
        switch_a{switch_a}, switch_b{switch_b}, switch_invert{switch_invert} {
    }
    bool is_pressed() const override {
      return switch_a.is_pressed() && switch_b.is_pressed() && !switch_invert.is_pressed();
    }
};

}

#endif
