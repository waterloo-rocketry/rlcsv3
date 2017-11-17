#ifndef TOWER_GLOBALS_H
#define TOWER_GLOBALS_H

#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif


//state that the client last asked us to do
actuator_state_t* get_requested_state();
//state that we are currently outputting to the actuators
actuator_state_t* get_current_state();

daq_holder_t* get_global_current_daq();

void apply_state();
void reset_request();

//global functions that we just need
void init_outputs();

#ifdef __cplusplus
}
#endif

#endif //ifndef TOWER_GLOBALS_H
