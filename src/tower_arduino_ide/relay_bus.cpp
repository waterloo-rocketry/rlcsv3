#include "relay_bus.h"

uint8_t relay_bus_write(uint8_t addr, uint8_t data) {
	Wire.begin();	
	Wire.beginTransmission(addr); // transmit to device #4
	Wire.write(data);        // sends 1 byte
	Wire.endTransmission();    // stop transmitting
	return 1;
}

uint8_t relay_bus_read(uint8_t addr) {
	return 1;
}