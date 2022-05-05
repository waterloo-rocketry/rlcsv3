#include "config.hpp"
#include "pinout.hpp"

namespace Config {

const uint16_t SEND_STATUS_INTERVAL_MS = 300;

Switch::Switch *switches[NUM_ACTUATORS];
Channel::Channel *channels[NUM_SENSORS];

Switch::Missile primary_arm {32};
Switch::Missile secondary_arm {31};
Switch::Missile fire {30, true};

void setup() {
  switches[ActuatorID::fill_valve] = new Switch::Missile(33);
  switches[ActuatorID::vent_valve] = new Switch::Missile(37);
  switches[ActuatorID::injector_valve] = new Switch::Missile(35);
  switches[ActuatorID::ignition] = new Switch::Ignition(primary_arm, fire, secondary_arm);

  channels[SensorID::rlcs_main_batt_mv] = new Channel::Numeric("TM", 1, 10);
  channels[SensorID::rlcs_actuator_batt_mv] = new Channel::Numeric("TA", 1, 10);
  channels[SensorID::healthy_actuators] = new Channel::Numeric("HA", 1, 1);
  channels[SensorID::ignition_primary_ma] = new Channel::Numeric("IP", 1, 1);
  channels[SensorID::ignition_secondary_ma] = new Channel::Numeric("IS", 1, 1);
  channels[SensorID::fill_valve_state] = new Channel::Numeric("FL", 1, 1);
  channels[SensorID::vent_valve_state] = new Channel::Numeric("VN", 1, 1);
  channels[SensorID::injector_valve_state] = new Channel::Numeric("IJ", 1, 1);
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
