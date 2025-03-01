#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include "mock_arduino.hpp"
#include "shared_types.hpp"

// These types act as generic containers for actuators and sensors respectively. This forces
// code to expicitely refer to actuators and sensor by their names rather than generic indexes,
// which then lets the compiler ensure that there are no mismatches.
//
// Note: The reason these are structs and not classes (and don't have constructors) is so we can use named struct initialization, ie:
//    ActuatorMessage<bool> command = {
//        .valve_1 = true,
//        .valve_2 = false,
//        ...etc
//    };
// When we compile with -Wextra, gcc will warn us about missing members.

// Disable struct field padding
; // random semicolon to fix clangd warning bug, see: https://stackoverflow.com/questions/72456118/why-does-clang-give-a-warning-unterminated-pragma-pack-push-at-end-of-f
#pragma pack(push, 1)
struct ActuatorMessage {
  bool NV102; // NV-102 Fuel purge
  bool NV103; // NV-103 Fuel press
  bool NV104; // NV-104 Lox press
  bool NV105; // NV-105 Lox purge
  bool OV102;
  bool FV102;
  bool OV101v;
  bool FV101v;
  bool automatic_mode;
  bool sequence_a;
  bool sequence_b;
  bool start_sequence;
  bool ignition;

  bool operator==(const ActuatorMessage &other) const {
    return !memcmp(this, &other, sizeof(ActuatorMessage));
  }
};

ActuatorMessage build_safe_state(const ActuatorMessage &current_state);

struct SensorMessage {
  // Battery Voltages
  uint16_t towerside_main_batt_mv;
  uint16_t towerside_actuator_batt_mv;
  // Actuator health
  uint16_t error_code;
  bool towerside_armed;
  bool has_contact;
  // Ignition currents
  uint16_t ignition_ma;
  // states
  sequence::State state;
  char seq_step[4];
  unsigned long time_til_next;
};
#pragma pack(pop)

#endif
