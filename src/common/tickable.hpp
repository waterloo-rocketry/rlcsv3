#ifndef TICKER_H
#define TICKER_H

#include <stdint.h>

class Tickable {
  private:
    static uint8_t n; // initialized to 0
    static uint8_t cap; // initialized to 0
    static Tickable **instances; // initialized to nullptr
    virtual void tick() = 0;
  public:
    Tickable() {
      if (n == cap) {
        Tickable **newVec = new Tickable*[cap + 4];
        for (uint8_t i = 0; i < n; i++) {
          newVec[i] = instances[i];
        }
        delete [] instances;
        instances = newVec;
        cap += 4;
      }
      instances[n] = this;
      n++;
    }
    static void trigger_tick() {
      for (uint8_t i = 0; i < n; i++) {
        instances[i]->tick();
      }
    }
};

#endif
