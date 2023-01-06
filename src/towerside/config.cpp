#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"

namespace config {

struct Actuators {
  actuator::I2C valve_1 {1};
  actuator::I2C valve_2 {2};
  actuator::I2C valve_3 {3};
  actuator::I2C injector_valve {4};
  actuator::I2C ignition_primary {5};
  actuator::I2C ignition_secondary {6};
} ACTUATORS;

void apply(const ActuatorContainer<bool> &command) {
  ACTUATORS.valve_1.set(command.valve_1);
  ACTUATORS.valve_2.set(command.valve_2);
  ACTUATORS.valve_3.set(command.valve_3);
  ACTUATORS.injector_valve.set(command.injector_valve);
  ACTUATORS.ignition_primary.set(command.ignition_primary);
  ACTUATORS.ignition_secondary.set(command.ignition_secondary);
}

void apply_safe_state() {
  ACTUATORS.valve_1.set(false);
  ACTUATORS.valve_2.set(true);
  ACTUATORS.valve_3.set(false);
  // leave injector valve unchanged
  ACTUATORS.ignition_primary.set(false);
  ACTUATORS.ignition_secondary.set(false);
}

SensorContainer<uint16_t> build_sensor_message() {
  return SensorContainer<uint16_t> {
    .towerside_main_batt_mv = sensors::get_main_batt_mv(),
    .towerside_actuator_batt_mv = sensors::get_actuator_batt_mv(),
    .error_code = errors::pop(),
    .towerside_state = sensors::get_towerside_state(),
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
