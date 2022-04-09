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
      char c;
      std::cin >> c;
      return c;
    }
    bool write(char c) override {
      std::cout << c;
      return true;
    }
};

extern MockSerial Serial;

unsigned long millis();

#endif
#endif
