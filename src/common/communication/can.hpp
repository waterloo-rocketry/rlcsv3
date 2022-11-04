#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "serializable.hpp"

namespace Communication {

class CANMessage: public Serializable {
  public:
    uint16_t sid = 0;
    uint8_t data[8] = {0};
    CANMessage() {}
    CANMessage(uint16_t sid, uint8_t data0 = 0, uint8_t data1 = 0, uint8_t data2 = 0, uint8_t data3 = 0,
      uint8_t data4 = 0, uint8_t data5 = 0, uint8_t data6 = 0, uint8_t data7 = 0):
      sid{sid}, data{data0, data1, data2, data3, data4, data5, data6, data7} {}

    static const uint8_t DATA_LENGTH = 10;
    bool decode(const uint8_t *buf) override {
      sid = ((uint16_t)(buf[0])) << 8;
      sid |= buf[1];
      for (uint8_t i = 0; i < 8; i++) {
        data[i] = buf[i + 2];
      }
      return true;
    }
    bool encode(uint8_t *buf) const override {
      buf[0] = (uint8_t)(sid >> 8);
      buf[1] = (uint8_t)(sid);
      for (uint8_t i = 0; i < 8; i++) {
        buf[i + 2] = data[i];
      }
      return true;
    }
};

}

#endif
