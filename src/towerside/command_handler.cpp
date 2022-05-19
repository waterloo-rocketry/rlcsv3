#include "command_handler.hpp"

namespace CommandHandler {

// Mapping from digits [list indices] to which segment LEDs need to be lit.
const uint8_t SevenSeg::digitMap[] = {
  // GFEDCBA            7-segment map:
  0b00111111, // 0          AAA
  0b00000110, // 1         F   B
  0b01011011, // 2         F   B
  0b01001111, // 3          GGG
  0b01100110, // 4         E   C
  0b01101101, // 5         E   C
  0b01111101, // 6          DDD  DP
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01110111, // A
  0b01111100, // b
  0b00111001, // C
  0b01011110, // d
  0b01111001, // E
  0b01110001  // F
};

// Mapping from LED segments (interpreted as A=0, B=1, ...) to output pins.
const uint8_t SevenSeg::pinoutMap[] = {
  Pinout::SEVENSEG_A,
  Pinout::SEVENSEG_B,
  Pinout::SEVENSEG_C,
  Pinout::SEVENSEG_D,
  Pinout::SEVENSEG_E,
  Pinout::SEVENSEG_F,
  Pinout::SEVENSEG_G
};

}
