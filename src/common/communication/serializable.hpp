#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stdint.h>

namespace Communication {

class Serializable {
  public:
    static const uint8_t DATA_LENGTH;
    virtual bool encode(uint8_t *buf) const = 0;
    virtual bool decode(const uint8_t *buf) = 0;
};

}

#endif
