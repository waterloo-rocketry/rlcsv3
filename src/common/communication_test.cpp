#include "communication.hpp"
#include "mock_arduino.hpp"
#include <iostream>

int data = 1145258561;
Communicator<int, int> comm{Serial, 300};

void setup() {}

void loop() {
  comm.read_byte();
  if (comm.get_message(&data)) {
    comm.send(data);
    std::cout << '\n';
    std::cout << (int)comm.seconds_since_last_contact() << '\n';
  }
}
