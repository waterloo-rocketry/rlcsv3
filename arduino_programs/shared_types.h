#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdint.h>

char fromBase64(char base64);
char toBase64(char binary);

//the main type for holding the state of the actuators
//can be used for desired or actual actuator state
//the definition of these in these comments are the canon
typedef struct {
    unsigned char remote_fill_valve;    //1 = open, 0 = closed
    unsigned char remote_vent_valve;    //1 = open, 0 = closed
    unsigned char run_tank_valve;       //1 = open, 0 = closed
    unsigned char injector_valve;       //1 = open, 0 = closed
    unsigned char linear_actuator;      //1 = retracted, 0 = extended
    unsigned char ignition_power;       //1 = firing, 0 = not firing
    unsigned char ignition_select;      //1 = secondary; 0 = primary
} actuator_state_t;

//these functions return 0 on failure, 1 on success.
int convert_radio_to_state(actuator_state_t* state, char binary);
int convert_state_to_radio(actuator_state_t* state, char* binary);

int actuator_compare(actuator_state_t* s, actuator_state_t* q);

typedef struct {

    uint16_t pressure1;                 //between 0 and 999
    uint16_t pressure2;                 //between 0 and 999
    uint16_t pressure3;
    uint16_t rocket_mass;               //between 0 and 999 (measured in decipounds. Don't judge me)
    uint16_t ign_pri_current;           //between 0 and 999 (measured in centiamps. these dumb units are for easy human readable output)
    uint16_t ign_sec_current;           //between 0 and 999 (measured in centiamps)
    unsigned char rfill_current_open;   //0 when current reading is below arbitrary limit
    unsigned char rfill_current_close;
    unsigned char rvent_current_open;
    unsigned char rvent_current_close;
    unsigned char linac_current_open;
    unsigned char linac_current_close;
    unsigned char rfill_lsw_open;       //0 when low, 1 when high (which means remote fill is open)
    unsigned char rfill_lsw_closed;     //0 when low, 1 when high (which means remote fill is closed)
    unsigned char rvent_lsw_open;       //0 when low, 1 when high (which means remote vent is open)
    unsigned char rvent_lsw_closed;     //0 when low, 1 when high (which means remote vent is closed)
    unsigned char rocketvent_lsw_open;
    unsigned char rocketvent_lsw_closed; //same as other valve limit switches
    unsigned char injectorvalve_lsw_open;
    unsigned char injectorvalve_lsw_closed;
    unsigned char linac_lsw_extend;     //0 when low, 1 when high (which means the actuator is extended)
    unsigned char linac_lsw_retract;    //0 when low, 1 when high (which means the actuator is retracted)

} daq_holder_t;

#define DAQ_RADIO_LEN 15
typedef struct {
	char data[DAQ_RADIO_LEN];
} daq_radio_value_t;
//these functions return 0 on failure, 1 on success.
int convert_radio_to_daq(daq_holder_t* daq, daq_radio_value_t* radio);
int convert_daq_to_radio(daq_holder_t* daq, daq_radio_value_t* radio);

#ifdef __cplusplus
}
#endif

#endif //ifndef SHARED_TYPES_H
