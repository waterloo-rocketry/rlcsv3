#ifndef TICKER_H
#define TICKER_H

#include <stdint.h>

// Tickable creates a list of all instances of its subclasses, and whenever the static Tickable::trigger_tick()
// is called, it calls the tick() function on all instances of its subclasses.
// Instances are stored in a dynamic array, but instead of doubling the length we just increase by 4 every time
// since we don't really care about this one-off performance hit compared to using less memory.
class Tickable {
  private:
    virtual void tick() = 0;
    // Use static functions instead of static variables so they can be initialized in-line.
    // We have to pull this shit because arduino won't compile cpp files in subdirectories, WTF.
    static uint8_t &n() { // number of elemenets in the array
      static uint8_t n_val = 0;
      return n_val;
    }
    static uint8_t &cap() { // total size of the allocated array
      static uint8_t cap_val = 0;
      return cap_val;
    }
    static Tickable **&instances() { // the allocated array
      static Tickable **instances_val = nullptr;
      return instances_val;
    }
  public:
    Tickable() {
      if (n() == cap()) { // If we need to grow the array of instances
        Tickable **newVec = new Tickable*[cap() + 4]; // increase the length by 4, allocate a new array
        for (uint8_t i = 0; i < n(); i++) { // copy over old values
          newVec[i] = instances()[i];
        }
        delete [] instances(); // deallocate old array
        instances() = newVec; // set stuff to point to new array
        cap() += 4;
      }
      instances()[n()] = this; // add this instance to the array
      n()++;
    }
    static void trigger_tick() {
      for (uint8_t i = 0; i < n(); i++) {
        instances()[i]->tick();
      }
    }
};

#endif
