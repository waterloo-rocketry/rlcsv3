#ifndef DEBUG_H
#define DEBUG_H

#ifndef ARDUINO

#include <iostream>

#define DEBUG(MSG) do { std::cerr << MSG << std::endl; } while (0);

#else

#define DEBUG(MSG)

#endif

#endif
