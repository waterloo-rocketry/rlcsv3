#ifndef CONFIG_H
#define CONFIG_H

#include "switches.hpp"
#include "channels.hpp"
#include "common/config.hpp"

namespace Config {

// All config variables defined in the .cpp
extern const uint16_t SEND_STATUS_INTERVAL_MS;
extern const uint16_t MESSAGE_WARNING_INTERVAL_S;

extern const uint16_t BATT_SCALE_NUM;
extern const uint16_t BATT_SCALE_DEN;

void setup();
Switch::Switch *get_switch(ActuatorID::ActuatorID id);
Channel::Channel *get_channel(SensorID::SensorID id);

}

#endif
