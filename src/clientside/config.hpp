#ifndef CONFIG_H
#define CONFIG_H

#include "switches.hpp"
#include "channels.hpp"
#include "common/config.hpp"

namespace Config {

extern const uint16_t SEND_STATUS_INTERVAL_MS;

void setup();
Switch::Switch *get_switch(ActuatorID::ActuatorID id);
Channel::Channel *get_channel(SensorID::SensorID id);

}

#endif
