#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"

namespace config {

struct Actuators {
  actuator::I2C ov101{1};
  actuator::I2C ov102{2};
  actuator::I2C nv101{3};
  actuator::I2C ov201{4};
  actuator::I2C ov202{5};
  actuator::I2C injector_valve{6};
  actuator::Ignition ignition_primary{7};
  actuator::Ignition ignition_secondary{8};
} ACTUATORS;

void apply(const ActuatorMessage &command) {
  ACTUATORS.ov101.set(command.ov101);
  ACTUATORS.ov102.set(command.ov102);
  ACTUATORS.nv101.set(command.nv101);
  ACTUATORS.ov201.set(command.ov201);
  ACTUATORS.ov202.set(command.ov202);
  ACTUATORS.injector_valve.set(command.injector_valve);
  ACTUATORS.ignition_primary.set(command.ignition_primary);
  ACTUATORS.ignition_secondary.set(command.ignition_primary); // fire both ignitions in response to ignition_primary
}

SensorMessage build_sensor_message() {
  return SensorMessage{
      .towerside_main_batt_mv = sensors::get_main_batt_mv(),
      .towerside_actuator_batt_mv = sensors::get_actuator_batt_mv(),
      .error_code = errors::pop(),
      .towerside_armed = sensors::is_armed(),
      .has_contact = sensors::has_contact(),
      .ignition_primary_ma = ACTUATORS.ignition_primary.get_current_ma(1),
      .ignition_secondary_ma = ACTUATORS.ignition_secondary.get_current_ma(1),
      .ov101_state = ACTUATORS.ov101.get_state(),
      .ov102_state = ACTUATORS.ov102.get_state(),
      .nv101_state = ACTUATORS.nv101.get_state(),
	  .ov201_state = ACTUATORS.ov201.get_state(),
  };
}

} // namespace config
