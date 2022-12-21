#include "switch.hpp"
#include "common/mock_arduino.hpp"
#include "pinout.hpp"

void InitSwitch() {
	pinMode(Pinout::KEY_SWITCH_IN, INPUT_PULLUP);
	pinMode(Pinout::KEY_SWITCH_GND, OUTPUT);
	digitalWrite(Pinout::KEY_SWITCH_GND, false);

	for (unsigned int i = 0;
		 i < (sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]));
		 i++) {
		pinMode(Pinout::MISSILE_LEDS[i], OUTPUT);
	}

	pinMode(Pinout::MISSILE_SWITCH_IGNITION_FIRE, INPUT_PULLUP);
}

void GetSwitchState(struct SwitchState *switch_state) {
	switch_state->key_switch = digitalRead(Pinout::KEY_SWITCH_IN) ^ 1;
	switch_state->missile_switch[0] = digitalRead(Pinout::MISSILE_SWITCH_1);
	switch_state->missile_switch[1] = digitalRead(Pinout::MISSILE_SWITCH_2);
	switch_state->missile_switch[2] = digitalRead(Pinout::MISSILE_SWITCH_3);
	switch_state->missile_switch[3] = digitalRead(Pinout::MISSILE_SWITCH_4);
	switch_state->missile_switch[4] = digitalRead(Pinout::MISSILE_SWITCH_5);
	switch_state->missile_switch[5] = digitalRead(Pinout::MISSILE_SWITCH_6);
	switch_state->missile_switch[6] = digitalRead(Pinout::MISSILE_SWITCH_7);
	switch_state->missile_switch[7] = digitalRead(Pinout::MISSILE_SWITCH_8);
	switch_state->missile_switch_injector
		= digitalRead(Pinout::MISSILE_SWITCH_INJECTOR);
	switch_state->missile_switch_ignition_pri
		= digitalRead(Pinout::MISSILE_SWITCH_IGNITION_PRI);
	switch_state->missile_switch_ignition_sec
		= digitalRead(Pinout::MISSILE_SWITCH_IGNITION_SEC);
	switch_state->missile_switch_ignition_fire
		= digitalRead(Pinout::MISSILE_SWITCH_IGNITION_FIRE) ^ 1;
}

void SetMissileLED(int *led_status) {
	for (unsigned int i = 0;
		 i < (sizeof(Pinout::MISSILE_LEDS) / sizeof(Pinout::MISSILE_LEDS[0]));
		 i++) {
		digitalWrite(Pinout::MISSILE_LEDS[i], led_status[i] ^ 1);
	}
}
