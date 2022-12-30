#include "communication.hpp"
#include "mock_arduino.hpp"
#include <iostream>

int data = 1145258561;
Communicator<int, int> comm{Serial};

void setup() {}

void loop() {
	bool b = comm.read_byte();
	if (comm.get_message(&data)) {
		comm.send(&data);
		std::cout << '\n';
	}
}
