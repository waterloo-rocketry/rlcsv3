#ifndef TOWER_DAQ_H
#define TOWER_DAQ_H

#include"shared_types.h"
#include"tower_pin_defines.h"


//call at startup. Sets pin modes, allocates space, whatever
void init_daq_pins();

//read the daq values into window array. Call this function very regularly
void read_daq_pins();

//perform filtering from window array. Call when you need the values
void compute_daq_values(daq_holder_t* output);

#endif
