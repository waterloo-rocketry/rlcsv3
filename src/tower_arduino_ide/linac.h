#ifndef LINAC_H_
#define LINAC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//linear actuator handling library
//depends on PIN_LINACTUATOR_{POWER,SELECT} being defined
//Whadya mean that's not how I should be building libraries?

//called at startup
void linac_init();

//called every main program loop. Decides whether it's time to stop
//applying power to the linear actuator. Please don't delay in calling
//this function, since that could maybe cause a fire. Which'd be bad.
void linac_refresh();

//api calls. Return true if the desired action can be taken. Eg, if you
//call linac_extend, it will return true if the linac is retracted, and
//it's not currently in a cooldown state
uint8_t linac_extend();
uint8_t linac_retract();

#ifdef __cplusplus
}
#endif

#endif //ifnde LINAC_H_
