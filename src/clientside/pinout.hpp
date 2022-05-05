#ifndef PINOUT_H
#define PINOUT_H

#include <stdint.h>

namespace Pinout {

const uint8_t BATT_VOLTAGE = 0;

const uint8_t KEY_SWITCH_IN = 9;
const uint8_t KEY_SWITCH_GND = 10;

const uint8_t SEVENSEG_D1 = 47;
const uint8_t SEVENSEG_D2 = 46;
const uint8_t SEVENSEG_A  = 39;
const uint8_t SEVENSEG_B  = 40;
const uint8_t SEVENSEG_C  = 42;
const uint8_t SEVENSEG_D  = 44;
const uint8_t SEVENSEG_E  = 43;
const uint8_t SEVENSEG_F  = 41;
const uint8_t SEVENSEG_G  = 38;
const uint8_t SEVENSEG_DP = 45;

const uint8_t LCD_RS = 25;
const uint8_t LCD_EN = 24;
const uint8_t LCD_D4 = 29;
const uint8_t LCD_D5 = 27;
const uint8_t LCD_D6 = 28;
const uint8_t LCD_D7 = 26;

const uint8_t MISSILE_LEDS[] = {
  69,
  68,
  67,
  66,
  65,
  64,
  63,
  62,
  61,
  60,
  59
};

}

#endif
