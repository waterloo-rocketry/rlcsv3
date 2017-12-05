#ifndef TOWER_DAQ_H
#define TOWER_DAQ_H

#include"shared_types.h"

//how many samples to hold in our sliding window average
#define WINDOW_WIDTH 10;

//call at startup. Sets pin modes, allocates space, whatever
void init_daq_pins();

//read the daq values into window array. Call this function very regularly
void read_daq_pins();

//perform filtering from window array. Call when you need the values
void compute_daq_values(daq_holder_t* output);

#endif
