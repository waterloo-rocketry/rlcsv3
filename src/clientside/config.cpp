#include "config.hpp"
#include "pinout.hpp"

namespace Config {

const uint16_t SEND_STATUS_INTERVAL_MS = 200;
// if it has been this long since we heard from towerside show a warning
const uint16_t MESSAGE_WARNING_INTERVAL_S = 3;

// Experimentally verified
const uint16_t BATT_SCALE_NUM = 1;
const uint16_t BATT_SCALE_DEN = 7;
const uint16_t BATT_SCALE_PRE_OFFSET = -11; // pre-scaling offset (for better precision)

Switch::Switch *switches[NUM_ACTUATORS];
Channel::Channel *channels[NUM_SENSORS];

// Define common arming / firing switches since they are reused between primary and secondary ignition
Switch::Missile primary_arm {Pinout::MISSILE_SWITCH_IGNITION_PRI};
Switch::Missile secondary_arm {Pinout::MISSILE_SWITCH_IGNITION_SEC};
Switch::Missile fire {Pinout::MISSILE_SWITCH_IGNITION_FIRE, true};

// Initialize the switches and channels arrays
void setup() {
  switches[ActuatorID::valve_1] = new Switch::Missile(Pinout::MISSILE_SWITCH_1);
  switches[ActuatorID::valve_2] = new Switch::Missile(Pinout::MISSILE_SWITCH_2);
  switches[ActuatorID::valve_3] = new Switch::Missile(Pinout::MISSILE_SWITCH_3);
  switches[ActuatorID::linear_actuator] = new Switch::Missile(Pinout::MISSILE_SWITCH_4);
  switches[ActuatorID::injector_valve] = new Switch::Missile(Pinout::MISSILE_SWITCH_INJECTOR);
  switches[ActuatorID::ignition_primary] = new Switch::Ignition(primary_arm, fire, secondary_arm);
  switches[ActuatorID::ignition_secondary] = new Switch::Ignition(secondary_arm, fire, primary_arm);
  switches[ActuatorID::remote_arming] = new Switch::Missile(Pinout::MISSILE_SWITCH_5);
  switches[ActuatorID::remote_disarming] = new Switch::Missile(Pinout::MISSILE_SWITCH_6);

  channels[SensorID::towerside_main_batt_mv] = new Channel::Numeric("TM", 1, 100);
  channels[SensorID::towerside_actuator_batt_mv] = new Channel::Numeric("TA", 1, 100);
  channels[SensorID::healthy_actuators_count] = new Channel::Numeric("HA", 1, 1);
  channels[SensorID::towerside_state] = new Channel::Numeric("TS", 1, 1);
  channels[SensorID::ignition_primary_ma] = new Channel::Numeric("IP", 1, 10);
  channels[SensorID::ignition_secondary_ma] = new Channel::Numeric("IS", 1, 10);
  channels[SensorID::valve_1_state] = new Channel::ActuatorState("V1");
  channels[SensorID::valve_2_state] = new Channel::ActuatorState("V2");
  channels[SensorID::linear_actuator_state] = new Channel::ActuatorState("LN");
}

Switch::Switch *get_switch(ActuatorID::ActuatorID id) {
  if (id >= NUM_ACTUATORS) return nullptr;
  return switches[id];
}

Channel::Channel *get_channel(SensorID::SensorID id) {
  if (id > NUM_SENSORS) return nullptr;
  return channels[id];
}

}
