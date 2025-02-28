#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"
#include "sequence.hpp"

namespace config {

struct Actuators {
  actuator::I2C NV102{10};
  actuator::I2C NV103{2};
  actuator::I2C NV104{1};
  actuator::I2C NV105{11};
  actuator::I2C OV102{6};
  actuator::I2C FV102{7};
  actuator::I2C OV101v{3};
  actuator::I2C FV101v{4};
  actuator::Ignition ignition{5};
} ACTUATORS;

void apply(const ActuatorMessage &command) {
  ACTUATORS.NV102.set(!command.NV102);
  ACTUATORS.NV103.set(command.NV103);
  ACTUATORS.NV104.set(command.NV104);
  ACTUATORS.NV105.set(!command.NV105);
  ACTUATORS.OV102.set(!command.OV102);
  ACTUATORS.FV102.set(!command.FV102);
  ACTUATORS.OV101v.set(!command.OV101v);
  ACTUATORS.FV101v.set(!command.FV101v);
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
      .state = sequence::get_state(),
  };
}

} // namespace config
