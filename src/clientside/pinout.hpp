#ifndef PINOUT_H
#define PINOUT_H

#include <stdint.h>

namespace Pinout {

const uint8_t MAIN_BATT_VOLTAGE = 0;
const uint8_t ACTUATOR_BATT_VOLTAGE = 3;
const uint8_t KEY_SWITCH_IN = 18;
const uint8_t KEY_SWITCH_GND = 19;

const uint8_t SEVENSEG_D1 = 43;
const uint8_t SEVENSEG_D2 = 39;
const uint8_t SEVENSEG_A  = 38;
const uint8_t SEVENSEG_B  = 42;
const uint8_t SEVENSEG_C  = 37;
const uint8_t SEVENSEG_D  = 45;
const uint8_t SEVENSEG_E  = 41;
const uint8_t SEVENSEG_F  = 46;
const uint8_t SEVENSEG_G  = 40;
const uint8_t SEVENSEG_DP = 44;

}

#endif
