#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include "mock_arduino.hpp"

template<typename ST, typename RT>
class Communicator {
	Stream &stream;
	uint8_t receive_buffer[sizeof(RT)];
	int buffer_position = 0;
	public:
	Communicator(Stream &stream): stream{stream} {}

	// loops through send_data and sends each byte
	bool send(ST *send_data) {
		bool status = true;
		uint8_t *byte = reinterpret_cast<uint8_t*>(send_data);
		for (int i = 0; i < sizeof(ST); ++i) {
			status &= stream.write(send_data + i);
		}
		return status;
	}

	// returns nullptr on failure, 
	const RT *get_message(RT *dest) {
		if (buffer_position < sizeof(RT)) {
			return nullptr;
		}

		RT *message = dynamic_cast<RT*>(receive_buffer);

		return message;
	}

	bool read_byte() {
		if (!stream.available()) {
			return false;
		}
		receive_buffer[buffer_position++] = static_cast<uint8_t>(stream.read());
		return true;
	}
};

#endif