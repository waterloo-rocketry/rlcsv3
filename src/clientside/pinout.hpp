#ifndef PINOUT_HPP
#define PINOUT_HPP

#include <stdint.h>

namespace Pinout {

	// Analog input for clientside's (divided) battery voltage
	const uint8_t BATT_VOLTAGE = 0;

	const uint8_t KEY_SWITCH_IN = 9;
	const uint8_t KEY_SWITCH_GND = 10;

	const uint8_t MISSILE_SWITCH_1 = 33;
	const uint8_t MISSILE_SWITCH_2 = 37;
	const uint8_t MISSILE_SWITCH_3 = 35;
	const uint8_t MISSILE_SWITCH_4 = 36;
	const uint8_t MISSILE_SWITCH_5 = 19;
	const uint8_t MISSILE_SWITCH_6 = 18;
	const uint8_t MISSILE_SWITCH_7 = 17;
	const uint8_t MISSILE_SWITCH_8 = 16;
	const uint8_t MISSILE_SWITCH_INJECTOR = 34;
	const uint8_t MISSILE_SWITCH_IGNITION_PRI = 32;
	const uint8_t MISSILE_SWITCH_IGNITION_SEC = 31;
	const uint8_t MISSILE_SWITCH_IGNITION_FIRE = 30;

	const uint8_t LCD_RS = 25;
	const uint8_t LCD_EN = 24;
	const uint8_t LCD_D4 = 29;
	const uint8_t LCD_D5 = 27;
	const uint8_t LCD_D6 = 28;
	const uint8_t LCD_D7 = 26;

	const uint8_t LED_RED = 11;
	const uint8_t LED_GREEN = 12;
	const uint8_t LED_BLUE = 13;

	// LEDs inside the missile switches to show the armed state
	const uint8_t MISSILE_LEDS[] = {69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59};

	// Seven segment display on the power board
	const uint8_t SEVENSEG_D1 = 47;
	const uint8_t SEVENSEG_D2 = 46;
	const uint8_t SEVENSEG_A = 39;
	const uint8_t SEVENSEG_B = 40;
	const uint8_t SEVENSEG_C = 42;
	const uint8_t SEVENSEG_D = 44;
	const uint8_t SEVENSEG_E = 43;
	const uint8_t SEVENSEG_F = 41;
	const uint8_t SEVENSEG_G = 38;
	const uint8_t SEVENSEG_DP = 45;

} // namespace Pinout

#endif
