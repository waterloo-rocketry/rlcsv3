#ifndef HAL_H
#define HAL_H

#ifndef ARDUINO

class MockSerial {
  public:
    void print(const char *msg);
    void println(const char *msg);
};

extern MockSerial Serial;

#endif
#endif
