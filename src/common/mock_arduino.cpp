#include "mock_arduino.hpp"

extern void setup();
extern void loop();

MockSerial Serial;

unsigned long millis() {
  static unsigned long n = 0;
  return n++;
}

int main() {
  setup();
  while (true) {
    loop();
  }
}
