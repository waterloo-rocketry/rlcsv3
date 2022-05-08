#ifndef CHANNELS_H
#define CHANNELS_H

#include <stdint.h>
#include "common/shared_types.hpp"
#include "common/mock_arduino.hpp"
#include "common/tickable.hpp"

namespace Channel {

class Channel {
  public:
    virtual const char *get_id() = 0;
    virtual uint8_t format(uint16_t val, char *buf) = 0;
};

class Numeric: public Channel {
  const char *id;
  uint16_t scaling_num;
  uint16_t scaling_den;
  public:
    Numeric(const char *id, uint16_t scaling_num, uint16_t scaling_den):
        id{id}, scaling_num{scaling_num}, scaling_den{scaling_den} {}
    const char *get_id() override {
      return id;
    }
    uint8_t format(uint16_t val, char *buf) override {
      if (val == SENSOR_ERR_VAL) {
        strncpy(buf, "ERR", 3);
        return 3;
      }
      val = val * scaling_num / scaling_den;
      if (val > 999) {
        strncpy(buf, "BIG", 3);
        return 3;
      }
      // Move to a temporary string so we don't write the null terminator to buf
      char tmp[4];
      snprintf(tmp, 4, "%03u", val);
      strncpy(buf, tmp, 3);
      return 3;
    }
};

class ActuatorState: public Channel {
  const char *id;
  public:
    ActuatorState(const char *id): id{id} {}
    const char *get_id() override {
      return id;
    }
    uint8_t format(uint16_t val, char *buf) override {
      if (val > 3) { // invalid value
        strncpy(buf, "ERR", 3);
        return 3;
      }
      ActuatorPosition position = static_cast<ActuatorPosition>(val);
      if (position == ActuatorPosition::open) {
        strncpy(buf, "OPN", 3);
      } else if (position == ActuatorPosition::closed) {
        strncpy(buf, "CLS", 3);
      } else if (position == ActuatorPosition::unknown) {
        strncpy(buf, "UNK", 3);
      } else {
        strncpy(buf, "ERR", 3);
      }
      return 3;
    }
};

}

#endif
