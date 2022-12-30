#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <cstring>
#include "mock_arduino.hpp"
#include "config.hpp"

#include <iostream>

template<typename ST, typename RT>
class Communicator {
	Stream &stream;
	// Note, buffer size will depend on 
	// the encoding and decoding protocol used
	static const size_t BUFF_SIZE = sizeof(RT) + 2;
	uint8_t receive_buffer[BUFF_SIZE];

	int buffer_position = 0;
	unsigned long time_of_last_byte = 0;
	const uint16_t max_delay_between_bytes;
	public:
	Communicator(Stream &stream, uint16_t max_delay_between_bytes = 300):
		stream{stream},
		max_delay_between_bytes{max_delay_between_bytes} {}

	// loops through send_data and sends each byte
	bool send(ST &send_data) {
		bool status = true;
		uint8_t *byte = reinterpret_cast<uint8_t*>(&send_data);

		/*
		Note, if you ever wanna send data with different encoding 
		and decoding protocols, just specalize this template.
		*/

		stream.write('W');
		for (int i = 0; i < sizeof(ST); ++i) {
			status &= stream.write(*(byte + i));
		}
		stream.write('R');
		return status;
	}

	// returns nullptr on failure, 
	bool get_message(RT *dest) {
		if (buffer_position < BUFF_SIZE) {
			return false;
		}

		if (receive_buffer[0] != 'W' || receive_buffer[sizeof(RT) + 1] != 'R') {
			buffer_position = 0;
			return false;
		}

		memcpy(dest, receive_buffer + 1, sizeof(RT));

		buffer_position = 0;
		return true;
	}

	bool read_byte() {
		if (stream.available()) {
			if (buffer_position < BUFF_SIZE) {
				receive_buffer[buffer_position++] = static_cast<uint8_t>(stream.read());
			}
			time_of_last_byte = millis();
			return true;
		} else if (millis() - time_of_last_byte > max_delay_between_bytes) {
			buffer_position = 0;
		}

		return false;
	}
};

#endif