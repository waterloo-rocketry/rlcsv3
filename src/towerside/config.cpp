#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"

namespace config {

struct Actuators {
  actuator::I2C valve_1 {1};
  actuator::I2C valve_2 {2};
  actuator::I2C valve_3 {3};
  actuator::I2C injector_valve {6};
  actuator::Ignition ignition_primary {4};
  actuator::Ignition ignition_secondary {5};
} ACTUATORS;

void apply(const ActuatorMessage &command) {
  ACTUATORS.valve_1.set(command.valve_1);
  ACTUATORS.valve_2.set(command.valve_2);
  ACTUATORS.valve_3.set(command.valve_3);
  ACTUATORS.injector_valve.set(command.injector_valve);
  ACTUATORS.ignition_primary.set(command.ignition_primary);
  ACTUATORS.ignition_secondary.set(command.ignition_secondary);
}

ActuatorMessage build_safe_state(const ActuatorMessage &current_state) {
  return ActuatorMessage {
    .valve_1 = false,
    .valve_2 = true,
    .valve_3 = false,
    .injector_valve = current_state.injector_valve,
    .ignition_primary = false,
    .ignition_secondary = false,
  };
}

SensorMessage build_sensor_message() {
  return SensorMessage {
    .towerside_main_batt_mv = sensors::get_main_batt_mv(),
    .towerside_actuator_batt_mv = sensors::get_actuator_batt_mv(),
    .error_code = errors::pop(),
    .towerside_armed = sensors::is_armed(),
    .has_contact = sensors::has_contact(),
    .ignition_primary_ma = ACTUATORS.ignition_primary.get_current_ma(1),
    .ignition_secondary_ma = ACTUATORS.ignition_secondary.get_current_ma(1),
    .valve_1_state = ACTUATORS.valve_1.get_state(),
    .valve_2_state = ACTUATORS.valve_2.get_state(),
    .valve_3_state = ACTUATORS.valve_3.get_state(),
    .injector_valve_state = ACTUATORS.injector_valve.get_state(),
  };
}

const uint8_t COMMUNICATION_TIMEOUT_S = 10; // Go to safe state after this many seconds without contact
const uint8_t COMMUNICATION_RESET_MS = 50; // maximum time between successive characters in the same message
const uint16_t SENSOR_MSG_INTERVAL_MS = 100; // Rate to send sensor messages at

} // namespace config
