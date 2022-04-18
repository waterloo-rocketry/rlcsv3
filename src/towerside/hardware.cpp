#include "hardware.hpp"
#include "common/mock_arduino.hpp"

namespace Hardware {

void setup() {
  Wire.begin();
  Wire.setWireTimeout(1000, true); // 1000uS = 1mS timeout, true = reset the bus in this case.
}

}
