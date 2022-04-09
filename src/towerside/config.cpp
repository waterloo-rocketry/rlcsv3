#include "config.hpp"

namespace Config {

Actuator *actuators[NUM_ACTUATORS];
Sensor *sensors[NUM_SENSORS];
ActuatorCommand default_states;
ActuatorCommand safe_states;

void setup() {
  actuators[ActuatorID::fill_valve] = new I2CActuator(1);
  actuators[ActuatorID::vent_valve] = new I2CActuator(2);
  actuators[ActuatorID::injector_valve] = new I2CActuator(3);
  actuators[ActuatorID::ignition_primary] = new I2CActuator(4);
  actuators[ActuatorID::ignition_secondary] = new I2CActuator(5);

  default_states.set_actuator(ActuatorID::fill_valve, false);
  default_states.set_actuator(ActuatorID::vent_valve, false);
  default_states.set_actuator(ActuatorID::injector_valve, false);
  default_states.set_actuator(ActuatorID::ignition_primary, false);
  default_states.set_actuator(ActuatorID::ignition_secondary, false);

  safe_states.set_actuator(ActuatorID::fill_valve, false);
  safe_states.set_actuator(ActuatorID::vent_valve, true);
  safe_states.set_actuator(ActuatorID::injector_valve, false);
  safe_states.set_actuator(ActuatorID::ignition_primary, false);
  safe_states.set_actuator(ActuatorID::ignition_secondary, false);

  sensors[SensorID::rlcs_main_batt_mv] = new AnalogSensor();
  sensors[SensorID::rlcs_actuator_batt_mv] = new AnalogSensor();
  sensors[SensorID::ignition_primary_ma] = new I2CCurrentSensor();
  sensors[SensorID::ignition_secondary_ma] = new I2CCurrentSensor();
  sensors[SensorID::fill_valve_state] = new I2CLimitSwitchSensor();
  sensors[SensorID::vent_valve_state] = new I2CLimitSwitchSensor();
  sensors[SensorID::injector_valve_state] = new I2CLimitSwitchSensor();
}

Actuator *get_actuator(ActuatorID::ActuatorID id) {
  if (id >= NUM_ACTUATORS) return nullptr;
  return actuators[id];
}

Sensor *get_sensor(SensorID::SensorID id) {
  if (id > NUM_SENSORS) return nullptr;
  return sensors[id];
}

ActuatorCommand get_default_states() {
  return default_states;
}

ActuatorCommand get_safe_states() {
  return safe_states;
}

}
