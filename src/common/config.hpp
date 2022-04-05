#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <stdint.h>

namespace ActuatorID {

// not an enum class so we can use them to index arrays easily
enum ActuatorID {
  fill_valve,
  vent_valve,
  // linear_actuator,
  injector_valve,
  ignition_primary,
  ignition_secondary,
  NUM_ACTUATORS
};

} // namespace ActuatorID

using ActuatorID::NUM_ACTUATORS; // Bring into the global scope

namespace SensorID {

// not an enum class so we can use them to index arrays easily
enum SensorID {
  // Battery voltages
  rlcs_main_batt_mv,
  rlcs_actuator_batt_mv,
  // Ignition currents
  ignition_primary_ma,
  ignition_secondary_ma,
  // Actuator states
  fill_valve_state,
  vent_valve_state,
  // linear_actuator_state
  injector_valve_state,
/*
  // Comp DAQ values
  fill_tank_psi,
  fill_line_psi,
  rocket_tank_psi,
  rocket_mass_kg,
  // RocketCAN data
  canbus_boards_connected,
  canbus_is_powered,
  canbus_errors_detected,
  canbus_battery_mv,
  vent_battery_mv,
*/
  NUM_SENSORS
};

} // namespace SensorID

using SensorID::NUM_SENSORS; // Bring into the global scope

#endif
