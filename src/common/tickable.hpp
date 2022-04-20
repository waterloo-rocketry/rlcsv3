#ifndef TICKER_H
#define TICKER_H

#include <stdint.h>

class Tickable {
  private:
    virtual void tick() = 0;
    // Use static functions instead of static variables so they can be initialized in-line.
    // We have to pull this shit because arduino won't compile cpp files in subdirectories, WTF.
    static uint8_t &n() {
      static uint8_t n_val = 0;
      return n_val;
    }
    static uint8_t &cap() {
      static uint8_t cap_val = 0;
      return cap_val;
    }
    static Tickable **&instances() {
      static Tickable **instances_val = nullptr;
      return instances_val;
    }
  public:
    Tickable() {
      if (n() == cap()) {
        Tickable **newVec = new Tickable*[cap() + 4];
        for (uint8_t i = 0; i < n(); i++) {
          newVec[i] = instances()[i];
        }
        delete [] instances();
        instances() = newVec;
        cap() += 4;
      }
      instances()[n()] = this;
      n()++;
    }
    static void trigger_tick() {
      for (uint8_t i = 0; i < n(); i++) {
        instances()[i]->tick();
      }
    }
};

#endif
