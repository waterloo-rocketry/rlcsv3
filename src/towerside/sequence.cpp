#include "sequence.hpp"
#include "common/config.hpp"
#include "config.hpp"

namespace sequence {

void set_state(State &state, ActuatorMessage &current_cmd, unsigned long &start_time) {
  enum State old_state = state;

  switch (state) {
    case MANUAL:
      {
        if (current_cmd.injector_valve) {
          state = AUTOMATIC;
        }
        break;
      }
    case AUTOMATIC:
      {
        // If any thing changes, go to manual
        if (
          !current_cmd.ignition_fire &&  // active low
          current_cmd.ignition_primary && !current_cmd.ignition_secondary) {

          state = SEQUENCE1;
          start_time = millis();
        }

        if (
          !current_cmd.ignition_fire &&  // active low
          !current_cmd.ignition_primary && current_cmd.ignition_secondary) {

          state = SEQUENCE2;
          start_time = millis();
        }

        if (!current_cmd.injector_valve) {
          state = MANUAL;
        }
        break;
      }
    case SEQUENCE1:
      {
        // If any thing changes, go to manual
        if (!current_cmd.injector_valve) {
          state = MANUAL;
        }
        break;
      }
    case SEQUENCE2:
      {
        // If any thing changes, go to manual
        if (!current_cmd.injector_valve) {
          state = MANUAL;
        }
        break;
      }
  }
}

const int len1 = 10;
const int times1[] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900 };
const ActuatorMessage sequence1[] = {};  // SHould be the same length as above

bool apply_sequence_one(unsigned long delta_time) {
  int idx = 0;

  while (idx < len1 && times1[idx + 1] <= delta_time) ++idx;
  // at this point, TIME[idx] <= delta_time < TIME[idx]

  if (idx == len1 - 1) return true;

  config::apply(sequence1[idx]);
  return false;
}

const int len2 = 10;
const int times2[] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900 };
const ActuatorMessage sequence2[] = {};  // SHould be the same length as above

bool apply_sequence_two(unsigned long delta_time) {
  int idx = 0;

  while (idx < len2 && times2[idx + 1] <= delta_time) { ++idx; }
  // at this point, TIME[idx] <= delta_time < TIME[idx]

  if (idx == len2 - 1) return true;

  config::apply(sequence2[idx]);
  return false;
}
}