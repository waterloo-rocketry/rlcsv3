#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include<stdint.h>
#include<stdbool.h>

char fromBase64(char base64);
char toBase64(char binary);

//the main type for holding the state of the actuators
//can be used for desired or actual actuator state
//the definition of these in these comments are the canon
typedef struct {
    unsigned char remote_fill_valve;    //1 = open, 0 = closed
    unsigned char remote_vent_valve;    //1 = open, 0 = closed
    unsigned char ox_pres_valve;         //1 = open, 0 = closed
    unsigned char fuel_pres_valve;         //1 = open, 0 = closed
    unsigned char run_tank_valve;       //1 = open, 0 = closed
    unsigned char injector_valve;       //1 = open, 0 = closed
    unsigned char linear_actuator;      //1 = retracted, 0 = extended
    unsigned char ignition_power;       //1 = firing, 0 = not firing
    unsigned char ignition_select;      //1 = secondary; 0 = primary
} actuator_state_t;

//these functions return 0 on failure, 1 on success.
int convert_radio_to_state(actuator_state_t* state, char binary);
int convert_state_to_radio(const actuator_state_t* state, char* binary);

int actuator_compare(const actuator_state_t* s, const actuator_state_t* q);

typedef enum {
    DAQ_VALVE_OPEN,
    DAQ_VALVE_CLOSED,
    DAQ_VALVE_UNK,
    DAQ_VALVE_ILLEGAL
} valve_state_t;

typedef struct {
    uint16_t pressure1; //fill tank pressure
    uint16_t pressure2; //fill line pressure
    uint16_t pressure3; //rocket tank pressure
    uint16_t rocket_mass;                      //between 0 and 999 (measured in decipounds. Don't judge me)
    uint16_t ign_pri_current;                  //between 0 and 999 (measured in centiamps. these dumb units are for easy human readable output)
    uint16_t ign_sec_current;                  //between 0 and 999 (measured in centiamps)
    unsigned char rfill_lsw_open;              //0 when low, 1 when high (which means remote fill is open)
    unsigned char rfill_lsw_closed;            //0 when low, 1 when high (which means remote fill is closed)
    unsigned char rvent_lsw_open;              //0 when low, 1 when high (which means remote vent is open)
    unsigned char rvent_lsw_closed;            //0 when low, 1 when high (which means remote vent is closed)
    unsigned char linac_lsw_extend;            //0 when low, 1 when high (which means the actuator is extended)
    unsigned char linac_lsw_retract;           //0 when low, 1 when high (which means the actuator is retracted)
    unsigned char ox_pres_valve_lsw_open;      //0 when low, 1 when high (which means remote fill is open)
    unsigned char ox_pres_valve_lsw_closed;    //0 when low, 1 when high (which means remote fill is closed)

    // new data fields for RocketCAN stuff
    unsigned char num_boards_connected;
    unsigned char bus_is_powered;
    bool any_errors_detected;
    valve_state_t injector_valve_state;
    valve_state_t rocketvent_valve_state;

    uint32_t bus_batt_mv;
    uint32_t vent_batt_mv;
    uint32_t rlcs_main_batt_mv;
    uint32_t rlcs_actuator_batt_mv;
} daq_holder_t;

#define DAQ_RADIO_LEN 25
typedef struct {
	char data[DAQ_RADIO_LEN];
} daq_radio_value_t;
//these functions return 0 on failure, 1 on success.
int convert_radio_to_daq(daq_holder_t* daq, const daq_radio_value_t* radio);
int convert_daq_to_radio(const daq_holder_t* daq, daq_radio_value_t* radio);

#ifdef __cplusplus
}
#endif

#endif //ifndef SHARED_TYPES_H
