#ifndef TOWER_PIN_DEFINES_H
#define TOWER_PIN_DEFINES_H

#define PIN_REMOTEFILL_POWER 26
#define PIN_REMOTEFILL_SELECT 27

#define PIN_REMOTEVENT_POWER 25
#define PIN_REMOTEVENT_SELECT 24

#define PIN_LINACTUATOR_POWER 2    // set thease to some unused pins.
#define PIN_LINACTUATOR_SELECT 3   // because we aren't using disconnect

#define PIN_OX_PRES_VALVE_POWER 22
#define PIN_OX_PRES_VALVE_SELECT 23

#define PIN_FUEL_PRES_VALVE_POWER 9
#define PIN_FUEL_PRES_VALVE_SELECT 8

#define PIN_OX_INJECTOR_VALVE_POWER 36
#define PIN_OX_INJECTOR_VALVE_SELECT 37
#define PIN_FUEL_INJECTOR_VALVE_POWER 6
#define PIN_FUEL_INJECTOR_VALVE_SELECT 7

#define PIN_IGNITION_POWER 28
#define PIN_IGNITION_SELECT 29

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
#define PIN_LIMITSW_REMOTEFILL_OPN 34
#define PIN_LIMITSW_REMOTEFILL_CLS 35
#define PIN_LIMITSW_REMOTEVENT_OPN 33
#define PIN_LIMITSW_REMOTEVENT_CLS 32
#define PIN_LIMITSW_LINAC_EXT 31    //It's probably ok if we just leave thease pointing at the same pins as what is now the ox pres valve
#define PIN_LIMITSW_LINAC_RET 30
#define PIN_LIMITSW_OX_PRES_VALVE_OPN 31
#define PIN_LIMITSW_OX_PRES_VALVE_CLS 30
#define PIN_LIMITSW_FUEL_PRES_VALVE_OPN 3
#define PIN_LIMITSW_FUEL_PRES_VALVE_CLS 2
#define PIN_LIMITSW_OX_INJECTOR_VALVE_OPN 11
#define PIN_LIMITSW_OX_INJECTOR_VALVE_CLS 12
#define PIN_LIMITSW_FUEL_INJECTOR_VALVE_OPN 4
#define PIN_LIMITSW_FUEL_INJECTOR_VALVE_CLS 5

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
