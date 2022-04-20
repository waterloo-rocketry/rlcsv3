#ifndef HAL_H
#define HAL_H

#ifndef ARDUINO

#include <iostream>

class Stream {
  public:
    virtual bool available() = 0;
    virtual char read() = 0;
    virtual bool write(char c) = 0;
};

class MockSerial: public Stream {
  public:
    MockSerial() {
      std::cin >> std::noskipws;
    }
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
};

extern MockSerial Serial;

class TwoWire {
  public:
    void begin() {};
    void setWireTimeout(uint32_t timeout, bool reset_with_timeout) {}
    bool getWireTimeoutFlag() { return false; }
    void clearWireTimeoutFlag() {}
    void beginTransmission(uint8_t address) { std::cout << "I2C to " << (int)address << ": "; }
    uint8_t write(uint8_t byte) { std::cout << (int)byte << " "; return 1; }
    uint8_t endTransmission() { std::cout << std::endl; return 0; }
    uint8_t requestFrom(uint8_t address, uint8_t length) { return length; }
    uint8_t read() { return 3; }
};

extern TwoWire Wire;

unsigned long millis();
uint16_t analogRead(uint8_t);
bool digitalRead(uint8_t);
void digitalWrite(uint8_t, bool);
void pinMode(uint8_t, bool);
#define INPUT true
#define INPUT_PULLUP true
#define OUTPUT false

#else

#include <Arduino.h>
#include <Wire.h>

#endif

#endif
