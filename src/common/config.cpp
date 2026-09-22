#include "config.hpp"

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage{
      .nv101 = false,
      .nv102 = false,
      .iv201 = false,
      .tank_heating_1 = false,
      .tank_heating_2 = false,
      .ignition_primary = false,
      .ignition_secondary = false,
  };
}