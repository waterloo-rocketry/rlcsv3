#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"

namespace config {

struct Actuators {
  actuator::I2C NV102{1};
  actuator::I2C NV103{2};
  actuator::I2C NV104{3};
  actuator::I2C NV105{4};
  actuator::I2C OV102{6};
  actuator::I2C FV102{7};
  actuator::I2C OV101v{16};
  actuator::I2C FV101v{17};
  actuator::Ignition ignition{12};
} ACTUATORS;

void apply(const ActuatorMessage &command) {
  ACTUATORS.NV102.set(command.NV102);
  ACTUATORS.NV103.set(command.NV103);
  ACTUATORS.NV104.set(command.NV104);
  ACTUATORS.NV105.set(command.NV105);
  ACTUATORS.OV102.set(command.OV102);
  ACTUATORS.FV102.set(command.FV102);
  ACTUATORS.OV101v.set(command.OV101v);
  ACTUATORS.FV101v.set(command.FV101v);
  ACTUATORS.ignition.set(command.ignition);
}

SensorMessage build_sensor_message() {
  return SensorMessage{
      .towerside_main_batt_mv = sensors::get_main_batt_mv(),
      .towerside_actuator_batt_mv = sensors::get_actuator_batt_mv(),
      .error_code = errors::pop(),
      .towerside_armed = sensors::is_armed(),
      .has_contact = sensors::has_contact(),
      .ignition_ma = ACTUATORS.ignition.get_current_ma(0),
      .NV102_state = ACTUATORS.NV102.get_state(),
      .NV103_state = ACTUATORS.NV103.get_state(),
      .NV104_state = ACTUATORS.NV104.get_state(),
      .NV105_state = ACTUATORS.NV105.get_state(),
      .OV102_state = ACTUATORS.NV105.get_state(),
      .FV102_state = ACTUATORS.NV105.get_state(),
      .OV101v_state = ACTUATORS.NV105.get_state(),
      .FV101v_state = ACTUATORS.NV105.get_state()
  };
}

} // namespace config
