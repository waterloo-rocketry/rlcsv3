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
      .ov103_state = ACTUATORS.ov103.get_state(),
      .heater_thermistor_1 = ACTUATORS.heater_1.get_thermistor(),
      .heater_thermistor_2 = ACTUATORS.heater_2.get_thermistor(),
      .heater_current_ma_1 = ACTUATORS.heater_1.get_current_ma(),
      .heater_current_ma_2 = ACTUATORS.heater_2.get_current_ma(),
      .heater_batt_mv_1 = ACTUATORS.heater_1.get_batt_voltage(),
      .heater_batt_mv_2 = ACTUATORS.heater_2.get_batt_voltage(),
      .heater_kelvin_low_mv_1 = ACTUATORS.heater_1.get_kelvin_low_voltage(),
      .heater_kelvin_low_mv_2 = ACTUATORS.heater_2.get_kelvin_low_voltage(),
      .heater_kelvin_high_mv_1 = ACTUATORS.heater_1.get_kelvin_high_voltage(),
      .heater_kelvin_high_mv_2 = ACTUATORS.heater_2.get_kelvin_high_voltage()
  };
}

} // namespace config
