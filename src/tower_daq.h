#ifndef TOWER_DAQ_H
#define TOWER_DAQ_H

#include"shared_types.h"

//how many samples to hold in our sliding window average
#define WINDOW_WIDTH 16

//call at startup. Sets pin modes, allocates space, whatever
void init_daq_pins();

//read the daq values into window array. Call this function very regularly
void read_daq_pins();

//perform filtering from window array. Call when you need the values
void compute_daq_values(daq_holder_t* output);

//scaling factors and other constants

/*
 * BASED ON CALIBRATION DONE ON JUNE 8TH
 * AT 12.49Vbatt:
 *  SP1: (278.92*vout - 74.42)PSI
 *  SP2: (278.66*vout - 120.43)PSI
 * AT 11.63Vbatt:
 *  SP1: (277.76*vout - 68.179)PSI
 *  SP2: (277.28*vout - 113.76)PSI
 */
#define PRESSURE1_SCALE ((278*5)/1024)
#define PRESSURE1_OFFSET (-71)

#define PRESSURE2_SCALE ((278*5)/1024)
#define PRESSURE2_OFFSET (-117)

#define MASS_SCALE 0.195
#define MASS_OFFSET (-30)

#define IGNPRI_SCALE 1.1
#define IGNPRI_OFFSET 0
#define IGNSEC_SCALE 1.1
#define IGNSEC_OFFSET 0

#endif
