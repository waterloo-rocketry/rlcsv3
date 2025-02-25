#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
    .NV102 = false, // NV-102 Fuel purge
    .NV103 = false, // NV-103 Fuel press
    .NV104 = false, // NV-104 Lox press
    .NV105 = false, // NV-105 Lox purge
    .OV102 = false,
    .FV102 = false,
    .OV101v = false,
    .FV101v = false,
    .automatic_mode = current_state.automatic_mode,
    .sequence_a = false,
    .sequence_b = false,
    .start_sequence = false,
  };
}
