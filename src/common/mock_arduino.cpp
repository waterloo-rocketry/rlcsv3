#include "mock_arduino.hpp"

extern void setup();
extern void loop();

MockSerial Serial;

int main() {
  setup();
  while (true) {
    loop();
  }
}
