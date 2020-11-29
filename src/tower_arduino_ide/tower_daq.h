#ifndef TOWER_DAQ_H
#define TOWER_DAQ_H

#include"shared_types.h"

//how many samples to hold in our sliding window average
#define WINDOW_WIDTH 16

#ifdef __cplusplus
extern "C" {
#endif
//call at startup. Sets pin modes, allocates space, whatever
void init_daq_pins();

//read the daq values into window array. Call this function very regularly
void read_daq_pins();

//perform filtering from window array. Call when you need the values
void compute_daq_values(daq_holder_t* output);

//scaling factors and other constants

#ifdef __cplusplus
}
#endif
/*
 * BASED ON CALIBRATION DONE ON JUNE 8TH
 * AT 12.49Vbatt:
 *  SP1: (278.92*vout - 74.42)PSI
 *  SP2: (278.66*vout - 120.43)PSI
 * AT 11.63Vbatt:
 *  SP1: (277.76*vout - 68.179)PSI
 *  SP2: (277.28*vout - 113.76)PSI
 */
#define PRESSURE1_SCALE 1.267
#define PRESSURE1_OFFSET (-20)

#define PRESSURE2_SCALE 1.224
#define PRESSURE2_OFFSET (-40)

#define MASS_SCALE 1.95
#define MASS_OFFSET (-300)

#define IGNPRI_SCALE 1.1
#define IGNPRI_OFFSET 0
#define IGNSEC_SCALE 1.1
#define IGNSEC_OFFSET 0

#define MAIN_BATT_SCALE (7.63)
#define MAIN_BATT_OFFSET 0
#define ACTUATOR_BATT_SCALE (7.63)
#define ACTUATOR_BATT_OFFSET 0

#endif
