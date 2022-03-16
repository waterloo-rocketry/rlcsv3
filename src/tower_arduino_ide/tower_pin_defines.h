#ifndef TOWER_PIN_DEFINES_H
#define TOWER_PIN_DEFINES_H

//pins for the arming key
#define PIN_KEY_SWITCH_GND    10
#define PIN_KEY_SWITCH_INPUT  9

//daq pins
#define PIN_DAQ_MASS A15 //A15 is being used as a placeholder for a bunch of sensors we aren't using
#define PIN_DAQ_PRESSURE1 A15
#define PIN_DAQ_PRESSURE2 A15
//battery voltage pins
#define PIN_BATTERY_MAIN A0
#define PIN_BATTERY_ACTUATORS A3

//pins for the seven segment display
#define PIN_SEVENSEG_D1 43 // old: 47
#define PIN_SEVENSEG_D2 39 // old: 46
#define PIN_SEVENSEG_A  38 // old: 39
#define PIN_SEVENSEG_B  42 // old: 40
#define PIN_SEVENSEG_C  37 // old: 43
#define PIN_SEVENSEG_D  45 // old: 45
#define PIN_SEVENSEG_E  41 // old: 42
#define PIN_SEVENSEG_F  46 // old: 41
#define PIN_SEVENSEG_G  40 // old: 38
#define PIN_SEVENSEG_DP 44 // old: 44

//pins for the SD card
#define PIN_SD_SS 53

#endif //ifndef TOWER_PIN_DEFINES_H
