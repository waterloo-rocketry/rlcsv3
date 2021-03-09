#ifndef TOWER_PIN_DEFINES_H
#define TOWER_PIN_DEFINES_H

#define PIN_IGNITION_POWER 28
#define PIN_IGNITION_SELECT 29

//pins for the arming key
#define PIN_KEY_SWITCH_GND    10
#define PIN_KEY_SWITCH_INPUT  9

//daq pins
#define PIN_DAQ_MASS A0 //A0 is being used as a placeholder for a bunch of sensors we aren't using
#define PIN_DAQ_PRESSURE1 A0
#define PIN_DAQ_PRESSURE2 A0
//current sensor pins
#define PIN_CURRENT_IGNITION_PRI A9
#define PIN_CURRENT_IGNITION_SEC A8
//battery voltage pins
#define PIN_BATTERY_MAIN A3
#define PIN_BATTERY_ACTUATORS A2
//limit switch pins
//#define PIN_LIMITSW_FUEL_INJECTOR_VALVE_OPN 4
//#define PIN_LIMITSW_FUEL_INJECTOR_VALVE_CLS 5

//pins for the seven segment display
#define PIN_SEVENSEG_D1 47
#define PIN_SEVENSEG_D2 46
#define PIN_SEVENSEG_A  39
#define PIN_SEVENSEG_B  40
#define PIN_SEVENSEG_C  43
#define PIN_SEVENSEG_D  45
#define PIN_SEVENSEG_E  42
#define PIN_SEVENSEG_F  41
#define PIN_SEVENSEG_G  38
#define PIN_SEVENSEG_DP 44

//pins for the SD card
#define PIN_SD_SS 53

#endif //ifndef TOWER_PIN_DEFINES_H
