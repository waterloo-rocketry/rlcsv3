#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <cstring>
#include "mock_arduino.hpp"

template<typename ST, typename RT>
class Communicator {
	Stream &stream;
	// Note, buffer size will depend on 
	// the encoding and decoding protocol used
	static const size_t BUFF_SIZE = sizeof(RT) + 2;
	uint8_t receive_buffer[BUFF_SIZE];

	size_t buffer_position = 0;
	unsigned long time_of_last_byte = 0;
	const unsigned long max_delay_between_bytes;
public:
	Communicator(Stream &stream, unsigned long max_delay_between_bytes = 300):
		stream{stream},
		max_delay_between_bytes{max_delay_between_bytes} {}

	// loops through send_data and sends each byte
	bool send(ST &send_data) {
		bool status = true;
		uint8_t *send_data_uint8 = reinterpret_cast<uint8_t*>(&send_data);

		stream.write('W');
		stream.write(send_data_uint8, sizeof(ST));
		stream.write('R');
		return status;
	}

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

	inline uint8_t seconds_since_last_contact() {return millis() - time_of_last_byte;}
};

#endif