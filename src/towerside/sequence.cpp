#include "sequence.hpp"
#include "common/config.hpp"
#include "config.hpp"

namespace sequence {

const int len1 = 3;
const SequenceItem sequence1[] = {
  SequenceItem{
    0, 
    "S01",
    ActuatorMessage{
      .NV102=false,
      .NV103=true,
      .NV104=true,
      .NV105=false,
      .OV102=false,
      .FV102=false,
      .OV101v=false,
      .FV101v=false,
      .ignition = false}
  },
  SequenceItem{
    3000, 
    "S11",
    ActuatorMessage{
      .NV102=false,
      .NV103=true,
      .NV104=true,
      .NV105=false,
      .OV102=true,
      .FV102=true,
      .OV101v=false,
      .FV101v=false,
      .ignition = false}
  },
  SequenceItem{
    13000, 
    "S12",
    ActuatorMessage{
      .NV102=true,
      .NV103=false,
      .NV104=false,
      .NV105=true,
      .OV102=false,
      .FV102=false,
      .OV101v=true,
      .FV101v=true,
      .ignition=true}
  },
  SequenceItem{
    16000, 
    "S13",
    ActuatorMessage{
      .NV102=false,
      .NV103=false,
      .NV104=false,
      .NV105=false,
      .OV102=false,
      .FV102=false,
      .OV101v=true,
      .FV101v=true,
      .ignition=false}
  },
  SequenceItem{
    18000,
    "N/A",
    ActuatorMessage{}
  }
};

const int len2 = 4;
const SequenceItem sequence2[] = {
  SequenceItem{
    0,
    "S20",
    ActuatorMessage{false,false,false,false,false,false,false,false,false,false,false,false,false}
  },
  SequenceItem{
    3000,
    "S21",
    ActuatorMessage{true,false,false,false,false,false,false,false,false,false,false,false,false}
  },
  SequenceItem{
    6000,
    "S22",
    ActuatorMessage{false,false,false,true,false,false,false,false,false,false,false,false,false}
  },
  SequenceItem{
    9000,
    "S23",
    ActuatorMessage{true,false,false,true,false,false,false,false,false,false,false,false,false}
  },
  SequenceItem{
    12000,
    "N/A",
    ActuatorMessage{}
  }
};

const SequenceItem* sequences[] = {sequence1, sequence2};

enum sequence::State state = sequence::State::MANUAL;
unsigned long start_time;

int idx;
int seq_id;
unsigned long time_til_next;

void set_state(enum sequence::State s) {
  state = s;
}

void find_state(ActuatorMessage &current_cmd) {
  enum State old_state = state;

  if (state == MANUAL) {
    if (current_cmd.automatic_mode) {
      state = AUTOMATIC;
    }
  } else if (state == AUTOMATIC) {
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
  } else if (state == SEQUENCE1) {
    if (!current_cmd.sequence_a ||
      current_cmd.sequence_b) {

      state = AUTOMATIC;
    }

    // If any thing changes, go to manual
    if (!current_cmd.automatic_mode) {
      state = MANUAL;
    }
  } else if (state == SEQUENCE2) {
    if (!current_cmd.sequence_b ||
      current_cmd.sequence_a) {

      state = AUTOMATIC;
    }

    // If any thing changes, go to manual
    if (!current_cmd.automatic_mode) {
      state = MANUAL;
    }
  }
}

void act_on_state(ActuatorMessage &current_cmd) {
  switch (state) {
    idx = -1;
    seq_id = 0;
    time_til_next = 0;
    case sequence::State::MANUAL: {
      config::apply(current_cmd);
      break;
    }
    case sequence::State::AUTOMATIC: {
      idx = -1;
      seq_id = 0;
      time_til_next = 0;
      break;
    }
    case sequence::State::SEQUENCE1: {
      if (sequence::apply_sequence(1)) {
        state = sequence::State::AUTOMATIC;
      }
      break;
    }
    case sequence::State::SEQUENCE2: {
      if (sequence::apply_sequence(2)) {
        state = sequence::State::AUTOMATIC;
      }
      break;
    }
  }
}

bool apply_sequence(const int &len, const SequenceItem sequence[]) {
  unsigned long delta_time = millis() - start_time;

  idx = 0;

  while (idx < len && sequence[idx + 1].time <= delta_time) { ++idx; }

  if (idx == len) {
    return true;
  }

  time_til_next = sequence[idx + 1].time - delta_time;

  config::apply(sequence[idx].valve_states);
  return false;
}

bool apply_sequence(int seq) {
  if (seq == 1) {
    seq_id = 1;
    return apply_sequence(len1, sequence1);
  } else if (seq == 2) {
    seq_id = 2;
    return apply_sequence(len2, sequence2);
  }
}

void update_sensor_message(SensorMessage &msg) {
  msg.state = state;
  if (state == sequence::State::MANUAL || state == sequence::State::AUTOMATIC) {
    msg.seq_step[0] = 0;
  } else {
    memcpy(&msg.seq_step, sequences[seq_id - 1][idx].step, 4);
    msg.seq_step[3] = 0;
  }
  msg.time_til_next = time_til_next;
}
}
