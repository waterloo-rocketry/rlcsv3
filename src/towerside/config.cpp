#include "config.hpp"
#include "pinout.hpp"

namespace Config {

const uint16_t SEND_STATUS_INTERVAL_MS = 300;
const uint16_t TIME_TO_SAFE_STATE_S = 10;
const uint16_t ACTUATOR_DISPATCH_INTERVAL_MS = 10;

Actuator::Actuator *actuators[NUM_ACTUATORS];
Sensor::Sensor *sensors[NUM_SENSORS];
ActuatorCommand default_states;
ActuatorCommand safe_states;

void setup() {
  actuators[ActuatorID::fill_valve] = new Actuator::OldI2C(1);
  actuators[ActuatorID::vent_valve] = new Actuator::OldI2C(2);
  actuators[ActuatorID::injector_valve] = new Actuator::OldI2C(3);
  actuators[ActuatorID::ignition] = new Actuator::OldI2C(4);

  default_states.set_actuator(ActuatorID::fill_valve, false);
  default_states.set_actuator(ActuatorID::vent_valve, false);
  default_states.set_actuator(ActuatorID::injector_valve, false);
  default_states.set_actuator(ActuatorID::ignition, false);

  safe_states.set_actuator(ActuatorID::fill_valve, false);
  safe_states.set_actuator(ActuatorID::vent_valve, true);
  safe_states.set_actuator(ActuatorID::injector_valve, false);
  safe_states.set_actuator(ActuatorID::ignition, false);

  sensors[SensorID::rlcs_main_batt_mv] = new Sensor::Analog(Pinout::MAIN_BATT_VOLTAGE, 3, 1, 0);
  sensors[SensorID::rlcs_actuator_batt_mv] = new Sensor::Analog(Pinout::ACTUATOR_BATT_VOLTAGE, 3, 1, 0);
  sensors[SensorID::healthy_actuators] = new Sensor::HealthyActuators(actuators);
  sensors[SensorID::ignition_primary_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::ignition], 0);
  sensors[SensorID::ignition_secondary_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::ignition], 1);
  sensors[SensorID::fill_valve_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::fill_valve]);
  sensors[SensorID::vent_valve_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::vent_valve]);
  sensors[SensorID::injector_valve_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::injector_valve]);
}

Actuator::Actuator *get_actuator(ActuatorID::ActuatorID id) {
  if (id >= NUM_ACTUATORS) return nullptr;
  return actuators[id];
}

Sensor::Sensor *get_sensor(SensorID::SensorID id) {
  if (id > NUM_SENSORS) return nullptr;
  return sensors[id];
}

const ActuatorCommand &get_default_states() {
  return default_states;
}

const ActuatorCommand &get_safe_states() {
  return safe_states;
}

}
