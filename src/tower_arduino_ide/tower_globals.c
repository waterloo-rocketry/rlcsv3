#include "tower_globals.h"
#include "tower_daq.h"
#include "tower_pin_defines.h"
#include "nodeio.ioio.h"
#include "sd_handler.h"
#include "linac.h"
#include "i2c.h"
#include "Arduino.h"

static actuator_state_t global_requested_state;
static actuator_state_t global_current_state = {
    .valve_1 = 0,
    .valve_2 = 0,
    .valve_3 = 0,
    .valve_4 = 0,
    .injector_valve = 0,
    .ignition_power = 0,
    .ignition_select = 0
};

static daq_holder_t global_current_daq;

actuator_state_t* get_requested_state(){
    return &global_requested_state;
}

actuator_state_t* get_current_state(){
    return &global_current_state;
}

daq_holder_t* get_global_current_daq(){
    compute_daq_values(&global_current_daq);
    return &global_current_daq;
}

//copies requested_state to current_state, then applies requested state
//to the outputs
void apply_state(){

    if(global_requested_state.valve_1 != global_current_state.valve_1){
        //we need to change the valve_1 to what requested wants
        global_current_state.valve_1 = global_requested_state.valve_1;
        if(global_current_state.valve_1){
            //open the valve_1
            i2c_set_valve_select(I2C_VALVE_1, 0);
            i2c_set_valve_power(I2C_VALVE_1, 1);
        } else {
            //close the valve_1
            i2c_set_valve_select(I2C_VALVE_1, 1);
            i2c_set_valve_power(I2C_VALVE_1, 1);
        }
    }

    if(global_requested_state.valve_2 != global_current_state.valve_2){
        //we need to change the valve_2 to what requested wants
        global_current_state.valve_2 = global_requested_state.valve_2;
        if(global_current_state.valve_2){
            //open the valve_2
            i2c_set_valve_select(I2C_VALVE_2, 0);
            i2c_set_valve_power(I2C_VALVE_2, 1);
        } else {
            //close the valve_2
            i2c_set_valve_select(I2C_VALVE_2, 1);
            i2c_set_valve_power(I2C_VALVE_2, 1);
        }
    }

    if(global_requested_state.valve_3 != global_current_state.valve_3){
        //we need to change the valve_2 to what requested wants
        global_current_state.valve_3 = global_requested_state.valve_3;
        if(global_current_state.valve_3){
            //open the valve_3
            i2c_set_valve_select(I2C_VALVE_3, 0);
            i2c_set_valve_power(I2C_VALVE_3, 1);
        } else {
            //close the valve_3
            i2c_set_valve_select(I2C_VALVE_3, 1);
            i2c_set_valve_power(I2C_VALVE_3, 1);
        }
    }

    if(global_requested_state.valve_4 != global_current_state.valve_4){
        //we need to change the valve_4 to what requested wants
        global_current_state.valve_4 = global_requested_state.valve_4;
        if(global_current_state.valve_4){
            //open the valve_4
            i2c_set_valve_select(I2C_VALVE_4, 0);
            i2c_set_valve_power(I2C_VALVE_4, 1);
        } else {
            //close the valve_4
            i2c_set_valve_select(I2C_VALVE_4, 1);
            i2c_set_valve_power(I2C_VALVE_4, 1);
        }
    }

    global_current_state.valve_3 = global_requested_state.valve_3;
    //tell nodeio.ioio that we want the vent to change
    if(global_requested_state.valve_3){
        //we want it open
        nio_set_vent_desired(VALVE_OPEN);
    }
    else {
        nio_set_vent_desired(VALVE_CLOSED);
    }

    global_current_state.injector_valve = global_requested_state.injector_valve;
    //tell nodeio.ioio that we want the injector to change and change the injector valves
    if(global_requested_state.injector_valve){
        //we want it open
        nio_set_inj_desired(VALVE_OPEN);
        //open it
            i2c_set_valve_select(I2C_VALVE_INJECTOR, 0);
            i2c_set_valve_power(I2C_VALVE_INJECTOR, 1);
    }
    else {
        nio_set_inj_desired(VALVE_CLOSED);
        // close it
            i2c_set_valve_select(I2C_VALVE_INJECTOR, 1);
            i2c_set_valve_power(I2C_VALVE_INJECTOR, 1);
    }

    if(global_requested_state.ignition_power != global_current_state.ignition_power){
        //we need to change the ignition_power to what requested wants
        global_current_state.ignition_power = global_requested_state.ignition_power;
        if(global_current_state.ignition_power){
            //decide whether to write to primary or secondary ignition
            if(global_requested_state.ignition_select) {
                //write to secondary
                i2c_set_valve_select(I2C_IGNITION, 0);
                i2c_set_valve_power(I2C_IGNITION, 1);
            } else {
                //write to primary
                i2c_set_valve_select(I2C_IGNITION, 1);
                i2c_set_valve_power(I2C_IGNITION, 1);
            }
        } else {
            //remove power from ignition circuit
            i2c_set_valve_power(I2C_IGNITION, 0);
        }
    }

    if(global_requested_state.ignition_select != global_current_state.ignition_select){
        //we need to change the ignition_select to what requested wants
        global_current_state.ignition_select = global_requested_state.ignition_select;
    }
}

//the client sent a NACK, so copy current state to requested state
void reset_request(){
    global_requested_state.valve_1 = global_current_state.valve_1;
    global_requested_state.valve_2 = global_current_state.valve_2;
    global_requested_state.valve_3 = global_current_state.valve_3;
    global_requested_state.valve_4 = global_current_state.valve_4;
    global_requested_state.injector_valve = global_current_state.injector_valve;
    global_requested_state.ignition_power = global_current_state.ignition_power;
    global_requested_state.ignition_select = global_current_state.ignition_select;
}

void init_outputs() {
    //close the valves. This is the safest startup state
    i2c_set_valve_select(I2C_VALVE_1, 1);
    i2c_set_valve_power(I2C_VALVE_1, 1);
    i2c_set_valve_select(I2C_VALVE_2, 1);
    i2c_set_valve_power(I2C_VALVE_2, 1);
    i2c_set_valve_select(I2C_VALVE_3, 1);
    i2c_set_valve_power(I2C_VALVE_3, 1);
    i2c_set_valve_select(I2C_VALVE_4, 1);
    i2c_set_valve_power(I2C_VALVE_4, 1);
    i2c_set_valve_select(I2C_VALVE_INJECTOR, 1);
    i2c_set_valve_power(I2C_VALVE_INJECTOR, 1);

    linac_init();

    //ignition, set to off by default
    i2c_set_valve_select(I2C_IGNITION, 0);
    i2c_set_valve_power(I2C_IGNITION, 0);
}

//called when client hasn't told us to do anything for a while
//assume comms are entirely lost, close all the valves (except the
//rocket tank vent valve)
void goto_safe_mode()
{
    enum {CLOSED = 0, OPEN} valve_states;
    //take the current requested state, set it to the safest possible
    //state, and then call apply_state
    actuator_state_t* requested = get_requested_state();

    requested->valve_1 = CLOSED;
    requested->valve_2 = OPEN;
    requested->valve_3 = CLOSED;
    requested->valve_4 = OPEN;
    requested->injector_valve = CLOSED;

    //turn off ignition
    requested->ignition_power = 0;
    requested->ignition_select = 0;


    //apply that state
    apply_state();

    //tell rocketCAN to depower the system bus
    nio_depower_bus();
}

void tower_handle_rocketcan_update(const system_state *update)
{
    global_current_daq.num_boards_connected = update->num_boards_connected;
    global_current_daq.any_errors_detected = update->any_errors_detected;
    global_current_daq.pressure3 = update->tank_pressure;
    global_current_daq.injector_valve_state = update->injector_valve_state;
    global_current_daq.rocketvent_valve_state = update->vent_valve_state;
    global_current_daq.bus_batt_mv = update->bus_battery_voltage_mv;
    global_current_daq.vent_batt_mv = update->vent_battery_voltage_mv;
    //TODO, log to rlcslog
}


void key_switch_init(){
    // tie the pin to GND
    pinMode(PIN_KEY_SWITCH_GND, OUTPUT);
    digitalWrite(PIN_KEY_SWITCH_GND, LOW);
    //set as input with pullup
    pinMode(PIN_KEY_SWITCH_INPUT, INPUT_PULLUP);
}

//global for how long it's been since the output log was flushed
//to the SD card
unsigned long global_time_last_output_flush = 0;
const unsigned long global_output_flush_interval = 10000;
//global for how long it's been since we logged daq values
unsigned long global_time_last_logged_daq = 0;
const unsigned long global_time_between_daq_logs = 1000;
