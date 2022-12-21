#ifndef SWITCH_HPP
#define SWITCH_HPP

struct SwitchState {
	int key_switch;
	int missile_switch[8]; // missile switch 1-8, has array index 0-7
	int missile_switch_injector;
	int missile_switch_ignition_pri;
	int missile_switch_ignition_sec;
	int missile_switch_ignition_fire;
};

void InitSwitch();
void GetSwitchState(struct SwitchState *switch_state);
void SetMissileLED(int *led_status);

#endif
