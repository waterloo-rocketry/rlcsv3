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
	unsigned long time_since_last_byte = 0;
	public:
	Communicator(Stream &stream): stream{stream} {}

	// loops through send_data and sends each byte
	bool send(ST *send_data) {
		bool status = true;
		uint8_t *byte = reinterpret_cast<uint8_t*>(send_data);

		/*
		Note, encoding protocol may varry
		*/

		stream.write('W');
		for (int i = 0; i < sizeof(ST); ++i) {
			status &= stream.write(*(byte + i));
		}
		stream.write('R');
		return status;
	}

	// returns nullptr on failure, 
	const RT *get_message(RT *dest) {
		if (buffer_position < BUFF_SIZE) {
			return nullptr;
		}

		/*
		Note, error checking and decoding protocal may varry
		*/

		if (receive_buffer[0] != 'W' || receive_buffer[sizeof(RT) + 1] != 'R') {
			buffer_position = 0;
			return nullptr;
		}

		memcpy(dest, receive_buffer + 1, sizeof(RT));

		buffer_position = 0;
		return dest;
	}

	bool read_byte() {
		if (stream.available()) {
			if (buffer_position < BUFF_SIZE) {
				char c = static_cast<uint8_t>(stream.read());
				receive_buffer[buffer_position++] = c;
			}
			time_since_last_byte = millis();
			return true;
		} else if (millis() - time_since_last_byte > Config::MAX_DELAY_BETWEEN_BYTES) {
			buffer_position = 0;
		}

		return false;
	}
};

#endif