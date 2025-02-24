#include "sequence.hpp"
#include "common/config.hpp"
#include "config.hpp"

namespace sequence {

void set_state(State &state, ActuatorMessage &current_cmd, unsigned long &start_time) {
  enum State old_state = state;

  switch (state) {
    case MANUAL:
      {
        if (current_cmd.automatic_mode) {
          state = AUTOMATIC;
        }
        break;
      }
    case AUTOMATIC:
      {
        // If any thing changes, go to manual
        if (current_cmd.start_sequence && current_cmd.sequence_a && !current_cmd.sequence_b) {
          state = SEQUENCE1;
          start_time = millis();
        }

        if (current_cmd.start_sequence && !current_cmd.sequence_a && current_cmd.sequence_b) {
          state = SEQUENCE2;
          start_time = millis();
        }
        if (!current_cmd.automatic_mode) {
          state = MANUAL;
        }
        break;
      }
    case SEQUENCE1:
      {
        if (current_cmd.start_sequence ||  // active low
          !current_cmd.sequence_a ||
          current_cmd.sequence_b) {

          state = AUTOMATIC;
        }

        // If any thing changes, go to manual
        if (!current_cmd.automatic_mode) {
          state = MANUAL;
        }
        break;
      }
    case SEQUENCE2:
      {
        if (current_cmd.start_sequence ||  // active low
          current_cmd.sequence_a ||
          !current_cmd.sequence_b) {

          state = AUTOMATIC;
        }

        // If any thing changes, go to manual
        if (!current_cmd.automatic_mode) {
          state = MANUAL;
        }
        break;
      }
  }
}

const int len1 = 3;
const int times1[] = { 0, 5000, 6000};
const ActuatorMessage sequence1[] = {
  ActuatorMessage{
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
  },
  ActuatorMessage{
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
  }
};  // SHould be the same length as above

const int len2 = 3;
const int times2[] = { 0, 3000, 4000};
const ActuatorMessage sequence2[] = {
  ActuatorMessage{
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false
  },
  ActuatorMessage{
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
  }
};  // SHould be the same length as above

bool apply_sequence(unsigned long delta_time, const int &len, const int times[], const ActuatorMessage sequence[]) {
  int idx = 0;

  while (idx < len && times[idx + 1] <= delta_time) { ++idx; }
  // at this point, TIME[idx] <= delta_time < TIME[idx]

  if (idx == len - 1) return true;

  config::apply(sequence[idx]);
  return false;
}

bool apply_sequence(int seq, unsigned long delta_time) {
    if (seq == 1) {
        return apply_sequence(delta_time, len1, times1, sequence1);
    } else if (seq == 2) {
        return apply_sequence(delta_time, len2, times2, sequence2);
    }
}
}
