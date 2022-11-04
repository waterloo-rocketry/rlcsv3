#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <stdint.h>

namespace ActuatorID {

// not an enum class so we can use them to index arrays easily
enum ActuatorID {
  valve_1,
  valve_2,
  valve_3,
  linear_actuator,
  injector_valve,
  ignition_primary,
  ignition_secondary,
  remote_arming,
  remote_disarming,
  NUM_ACTUATORS // keep this at the end, its value becomes the number of actuator IDs before it
};

} // namespace ActuatorID

using ActuatorID::NUM_ACTUATORS; // Bring into the global scope

namespace SensorID {

// not an enum class so we can use them to index arrays easily
enum SensorID {
  // Battery voltages
  towerside_main_batt_mv,
  towerside_actuator_batt_mv,
  // Actuator health
  healthy_actuators_count,
  towerside_state,
  // Ignition currents
  ignition_primary_ma,
  ignition_secondary_ma,
  // Actuator states
  valve_1_state,
  valve_2_state,
  //valve_3_state,
  linear_actuator_state,
  //injector_valve_state,
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

  NUM_SENSORS // keep this at the end, it stores the total number of sensors
};

} // namespace SensorID

using SensorID::NUM_SENSORS;

#endif
