#include "actuators.hpp"
#include "config.hpp"
#include "errors.hpp"
#include "sensors.hpp"

namespace config {

struct Actuators {
<<<<<<< HEAD
  actuator::I2C ov101{2};
  actuator::I2C ov102{3};
  actuator::I2C ov103{4};
  actuator::I2C nv201{5};
  actuator::I2C cdv401{6};
  actuator::I2C cdv402{7};
  actuator::I2C qd301{8};
  actuator::I2C pyro_valve{9};
  actuator::I2C rocket_charging{10};
=======
  actuator::I2C v305{2};
  actuator::I2C v301{3};
  actuator::I2C v405{4};
>>>>>>> 4633435 (Initial E-Pump spin test RLCS config)
  actuator::Ignition ignition_primary{1};
  actuator::Ignition ignition_secondary{11};
  actuator::Heater heater_1{16};
  actuator::Heater heater_2{17};
} ACTUATORS;

void apply(const ActuatorMessage &command) {
<<<<<<< HEAD
  ACTUATORS.ov101.set(command.ov101);
  ACTUATORS.ov102.set(command.ov102);
  ACTUATORS.ov103.set(command.ov103);
  ACTUATORS.nv201.set(command.nv201);
  ACTUATORS.cdv401.set(command.cdv401);
  ACTUATORS.cdv402.set(command.cdv402);
  ACTUATORS.qd301.set(command.qd301);
  ACTUATORS.pyro_valve.set(command.pyro_valve);
  ACTUATORS.rocket_charging.set(command.rocket_charging);
=======
  ACTUATORS.v305.set(command.v305);
  ACTUATORS.v301.set(command.v301);
  ACTUATORS.v405.set(command.v405);
>>>>>>> 4633435 (Initial E-Pump spin test RLCS config)
  ACTUATORS.ignition_primary.set(command.ignition_primary);
  ACTUATORS.ignition_secondary.set(command.ignition_secondary);
  ACTUATORS.heater_1.set(command.tank_heating_1);
  ACTUATORS.heater_2.set(command.tank_heating_2);
}

SensorMessage build_sensor_message() {
  return SensorMessage{
      .towerside_main_batt_mv = sensors::get_main_batt_mv(),
      .towerside_actuator_batt_mv = sensors::get_actuator_batt_mv(),
      .error_code = errors::pop(),
      .towerside_armed = sensors::is_armed(),
      .has_contact = sensors::has_contact(),
      .ignition_primary_ma = ACTUATORS.ignition_primary.get_current_ma(0),
<<<<<<< HEAD
      .ignition_secondary_ma = ACTUATORS.ignition_primary.get_current_ma(1),
      .ov101_state = ACTUATORS.ov101.get_state(),
      .ov102_state = ACTUATORS.ov102.get_state(),
      .cdv401_state = ACTUATORS.cdv401.get_state(),
      .nv201_state = ACTUATORS.nv201.get_state(),
=======
      .ignition_secondary_ma = ACTUATORS.ignition_secondary.get_current_ma(0),
      .v305_state = ACTUATORS.v305.get_state(),
      .v301_state = ACTUATORS.v301.get_state(),
      .v405_state = ACTUATORS.v405.get_state(),
>>>>>>> 4633435 (Initial E-Pump spin test RLCS config)
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
