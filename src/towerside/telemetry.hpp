#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include "common/communication/receiver.hpp"
#include "sensors.hpp"

namespace Telemetry {
/*
class ActuatorStateListener: public Communication::MessageHandler<Communication::CANMessage>, public Sensor::Sensor {
  uint8_t actuator_id;
  uint8_t cur_state = 0;
  uint8_t req_state = 0;
  public:
    ActuatorStateListener(uint8_t actuator_id): actuator_id{actuator_id} {}
    void handle(const Communication::CANMessage &msg) override {
      if ((msg.sid & 0x7E0) == 0x460 && msg.data[3] == actuator_id) {
        cur_state = msg.data[4];
        req_state = msg.data[5];
      }
    }
    uint16_t get_value() override {
      // map between different enums
      if (cur_state == 0) { return 1; }
      if (cur_state == 1) { return 2; }
      if (cur_state == 2) { return 0; }
      return 3;
    }
};*/
  
}

#endif
