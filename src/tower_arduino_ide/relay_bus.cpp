#include "relay_bus.h"

void relay_bus_init() {
	Wire.begin();
}

uint8_t relay_bus_write(uint8_t addr, uint8_t data) {
	Wire.beginTransmission(addr);	// transmit to device #4
	Wire.write(data);        		// sends the 1 byte of data
	Wire.endTransmission();			// stop transmitting
	return 1;
}

uint8_t relay_bus_read(uint8_t addr) {
	Wire.requestFrom(addr, 1);	// request 1 bytes from slave device #addr
	uint8_t is_overflow = 0;
	while(Wire.available()) { 
		char c = Wire.read();		// receive a byte as character
		++is_overflow;
	}
	return 1;
}

//#endif