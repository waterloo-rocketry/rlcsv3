#include "config.hpp"
#include "pinout.hpp"

namespace Config {

// How often to send our status (valve states, currents, DAQ data) to clientside
const uint16_t SEND_STATUS_INTERVAL_MS = 300;
// Go to safe state if we haven't heard from clientside in this long
const uint16_t TIME_TO_SAFE_STATE_S = 10;
// How often to send commands to the actuators
const uint16_t ACTUATOR_DISPATCH_INTERVAL_MS = 10;

Actuator::Actuator *actuators[NUM_ACTUATORS];
Sensor::Sensor *sensors[NUM_SENSORS];
ActuatorCommand default_states;
ActuatorCommand safe_states;

Actuator::Ignition ignition {5};

// Initialize the actuators and sensors arrays, along with default and safe states.
void setup() {
  actuators[ActuatorID::valve_1] = new Actuator::I2C(1);
  actuators[ActuatorID::valve_2] = new Actuator::I2C(2);
  actuators[ActuatorID::valve_3] = new Actuator::I2C(3);
  actuators[ActuatorID::injector_valve] = new Actuator::I2C(4);
  actuators[ActuatorID::ignition_primary] = ignition.primary_actuator();
  actuators[ActuatorID::ignition_secondary] = ignition.secondary_actuator();

  default_states.set_actuator(ActuatorID::valve_1, false);
  default_states.set_actuator(ActuatorID::valve_2, false);
  default_states.set_actuator(ActuatorID::valve_3, false);
  default_states.set_actuator(ActuatorID::injector_valve, false);
  default_states.set_actuator(ActuatorID::ignition_primary, false);
  default_states.set_actuator(ActuatorID::ignition_secondary, false);

  safe_states.set_actuator(ActuatorID::valve_1, false);
  safe_states.set_actuator(ActuatorID::valve_2, true);
  safe_states.set_actuator(ActuatorID::valve_3, false);
  safe_states.set_actuator(ActuatorID::injector_valve, false);
  safe_states.set_actuator(ActuatorID::ignition_primary, false);
  safe_states.set_actuator(ActuatorID::ignition_secondary, false);

  // analog scaling numbers come from ramping through battery voltages and making a line of best fit
  sensors[SensorID::towerside_main_batt_mv] = new Sensor::Analog(Pinout::MAIN_BATT_VOLTAGE, 48, 17, 127);
  sensors[SensorID::towerside_actuator_batt_mv] = new Sensor::Analog(Pinout::ACTUATOR_BATT_VOLTAGE, 48, 17, 0);
  sensors[SensorID::healthy_actuators_count] = new Sensor::HealthyActuators(actuators);
  sensors[SensorID::ignition_primary_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::ignition_primary], 1);
  sensors[SensorID::ignition_secondary_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::ignition_secondary], 1);
  sensors[SensorID::valve_1_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::valve_1]);
  sensors[SensorID::valve_2_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::valve_2]);
  sensors[SensorID::valve_3_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::valve_3]);
  sensors[SensorID::injector_valve_state] = new Sensor::ActuatorPosition(actuators[ActuatorID::injector_valve]);
  sensors[SensorID::valve_1_p_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::valve_1], 0);
  sensors[SensorID::valve_1_s_ma] = new Sensor::ActuatorCurrent(actuators[ActuatorID::valve_1], 1);
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
