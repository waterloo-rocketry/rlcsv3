#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#ifndef ARDUINO

#define __unused __attribute__((__unused__))

#include <iostream>
#include <stdint.h>

class Stream {
public:
	virtual bool available() = 0;
	virtual char read() = 0;
	virtual bool write(char c __unused) = 0;
	bool write(const uint8_t *c, size_t len) {
		bool output = true;
		for (size_t i = 0; i < len; ++i) {
			output &= write(*(c + i));
		}
		return output;
	}
};

class MockSerial : public Stream {
public:
	MockSerial() {
		std::cin >> std::noskipws;
	}
	void begin(int baud __unused) {}
	bool available() override {
		return true;
	}
	char read() override {
		char c = 0;
		std::cin >> c;
		return c;
	}
	bool write(char c) override {
		std::cout << c;
		return true;
	}

	template <typename T> void print(T t) {
		std::cout << t;
	}
};

extern MockSerial Serial;
extern MockSerial Serial2;
extern MockSerial Serial3;

class TwoWire {
public:
	void begin(){};
	void setClock(uint16_t clock __unused) {}
	void setWireTimeout(uint32_t timeout __unused, bool reset_with_timeout __unused) {}
	bool getWireTimeoutFlag() {
		return false;
	}
	void clearWireTimeoutFlag() {}
	void beginTransmission(uint8_t address) {
		std::cout << "I2C to " << (int)address << ": ";
	}
	uint8_t write(uint8_t byte __unused) {
		std::cout << (int)byte << " ";
		return 1;
	}
	uint8_t endTransmission() {
		std::cout << std::endl;
		return 0;
	}
	uint8_t requestFrom(uint8_t address __unused, uint8_t length) {
		return length;
	}
	uint8_t read() {
		return 3;
	}
};

extern TwoWire Wire;

class LiquidCrystal {
public:
	LiquidCrystal(uint8_t a __unused, uint8_t b __unused, uint8_t c __unused,
			uint8_t d __unused, uint8_t e __unused, uint8_t f __unused) {}
	void begin(int rows __unused, int cols __unused) {}
	void clear() {}

	template <typename T> void print(T t) {
		std::cout << t;
	}

	void setCursor(uint8_t col __unused, uint8_t row __unused) {}
};

unsigned long millis();
uint16_t analogRead(uint8_t);
bool digitalRead(uint8_t);
void digitalWrite(uint8_t, bool);
void pinMode(uint8_t, bool);
#define INPUT true
#define INPUT_PULLUP true
#define OUTPUT false

int main();

#else

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#endif

#endif
