#include "tower_globals.h"
#include "tower_daq.h"
#include "tower_pin_defines.h"
#include "nodeio.ioio.h"
#include "sd_handler.h"
#include "Arduino.h"

actuator_state_t global_requested_state, global_current_state;
daq_holder_t global_current_daq;

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
    //log this transition to the sd card
    char tolog;
    if(convert_state_to_radio(get_requested_state(), &tolog))
        if(sd_active())
            rlcslog_tower_apply_state(tolog);

    if(global_requested_state.remote_fill_valve != global_current_state.remote_fill_valve){
        //we need to change the remote_fill_valve to what requested wants
        global_current_state.remote_fill_valve = global_requested_state.remote_fill_valve;
        if(global_current_state.remote_fill_valve){
            //open the remote_fill_valve
            digitalWrite((uint8_t) PIN_REMOTEFILL_POWER, HIGH);
            digitalWrite((uint8_t) PIN_REMOTEFILL_SELECT, LOW);
        } else {
            //close the remote_fill_valve
            digitalWrite((uint8_t) PIN_REMOTEFILL_POWER, HIGH);
            digitalWrite((uint8_t) PIN_REMOTEFILL_SELECT, HIGH);
        }
    }

    if(global_requested_state.remote_vent_valve != global_current_state.remote_vent_valve){
        //we need to change the remote_vent_valve to what requested wants
        global_current_state.remote_vent_valve = global_requested_state.remote_vent_valve;
        if(global_current_state.remote_vent_valve){
            //open the remote_vent_valve
            digitalWrite((uint8_t) PIN_REMOTEVENT_POWER, HIGH);
            digitalWrite((uint8_t) PIN_REMOTEVENT_SELECT, LOW);
        } else {
            //close the remote_vent_valve
            digitalWrite((uint8_t) PIN_REMOTEVENT_POWER, HIGH);
            digitalWrite((uint8_t) PIN_REMOTEVENT_SELECT, HIGH);
        }
    }

    if(global_requested_state.run_tank_valve != global_current_state.run_tank_valve){
        //we need to change the run_tank_valve to what requested wants
        global_current_state.run_tank_valve = global_requested_state.run_tank_valve;
        //tell nodeio.ioio that we want the vent to change
        if(global_requested_state.run_tank_valve){
            //we want it open
            nio_set_vent_desired(VALVE_OPEN);
        }
        else {
            nio_set_vent_desired(VALVE_CLOSED);
        }
    }

    if(global_requested_state.injector_valve != global_current_state.injector_valve){
        global_current_state.injector_valve = global_requested_state.injector_valve;
        //tell nodeio.ioio that we want the injector to change
        if(global_requested_state.injector_valve){
            //we want it open
            nio_set_inj_desired(VALVE_OPEN);
        }
        else {
            nio_set_inj_desired(VALVE_CLOSED);
        }
    }

    if(global_requested_state.linear_actuator != global_current_state.linear_actuator){
        //we need to change the linear_actuator to what requested wants
        global_current_state.linear_actuator = global_requested_state.linear_actuator;
        if(global_current_state.linear_actuator){
            //retract the linear_actuator
            digitalWrite((uint8_t) PIN_LINACTUATOR_POWER, HIGH);
            digitalWrite((uint8_t) PIN_LINACTUATOR_SELECT, LOW);
        } else {
            //extend the linear_actuator
            digitalWrite((uint8_t) PIN_LINACTUATOR_POWER, HIGH);
            digitalWrite((uint8_t) PIN_LINACTUATOR_SELECT, HIGH);
        }
    }

    if(global_requested_state.ignition_power != global_current_state.ignition_power){
        //we need to change the ignition_power to what requested wants
        global_current_state.ignition_power = global_requested_state.ignition_power;
        if(global_current_state.ignition_power){
            //apply power to ignition circuit
            digitalWrite((uint8_t) PIN_IGNITION_POWER, HIGH);
        } else {
            //remove power from ignition circuit
            digitalWrite((uint8_t) PIN_IGNITION_POWER, LOW);
        }
    }

    if(global_requested_state.ignition_select != global_current_state.ignition_select){
        //we need to change the ignition_select to what requested wants
        global_current_state.ignition_select = global_requested_state.ignition_select;
        if(global_current_state.ignition_select){
            //apply power to ignition_select
            digitalWrite((uint8_t) PIN_IGNITION_SELECT, HIGH);
        } else {
            //remove power from ignition_select
            digitalWrite((uint8_t) PIN_IGNITION_SELECT, LOW);
        }
    }
}

//the client sent a NACK, so copy current state to requested state
void reset_request(){
    global_requested_state.remote_fill_valve = global_current_state.remote_fill_valve;
    global_requested_state.remote_vent_valve = global_current_state.remote_vent_valve;
    global_requested_state.run_tank_valve = global_current_state.run_tank_valve;
    global_requested_state.linear_actuator = global_current_state.linear_actuator;
    global_requested_state.ignition_power = global_current_state.ignition_power;
    global_requested_state.ignition_select = global_current_state.ignition_select;
}

void init_outputs(){
    pinMode(PIN_REMOTEFILL_POWER, OUTPUT);
    pinMode(PIN_REMOTEFILL_SELECT, OUTPUT);
    pinMode(PIN_REMOTEVENT_POWER, OUTPUT);
    pinMode(PIN_REMOTEVENT_SELECT, OUTPUT);
    pinMode(PIN_LINACTUATOR_POWER, OUTPUT);
    pinMode(PIN_LINACTUATOR_SELECT, OUTPUT);
    pinMode(PIN_IGNITION_POWER, OUTPUT);
    pinMode(PIN_IGNITION_SELECT, OUTPUT);

    //close the valves. This is the safest startup state
    //fill valve
    digitalWrite((uint8_t) PIN_REMOTEFILL_POWER, HIGH);
    digitalWrite((uint8_t) PIN_REMOTEFILL_SELECT, HIGH); //select pin going high should set it to close, if it's wired right

    //vent valve
    digitalWrite((uint8_t) PIN_REMOTEVENT_POWER, HIGH);
    digitalWrite((uint8_t) PIN_REMOTEVENT_SELECT, HIGH);

    //run tank valve
    //TODO, figure out how the run tank valve is going to work
    //likely involve a serial link to another arduino

    //linac, extend on startup
    digitalWrite((uint8_t) PIN_LINACTUATOR_POWER, HIGH);
    digitalWrite((uint8_t) PIN_LINACTUATOR_SELECT, HIGH);

    //ignition, set to off by default
    digitalWrite((uint8_t) PIN_IGNITION_POWER, LOW);
    digitalWrite((uint8_t) PIN_IGNITION_SELECT, LOW);
}

//called when client hasn't told us to do anything for a while
//assume comms are entirely lost, close all the valves (except the
//rocket tank vent valve)
void goto_safe_mode()
{
    //take the current requested state, set it to the safest possible
    //state, and then call apply_state
    actuator_state_t* requested = get_requested_state();

    //close both valves we have direct control over
    requested->remote_fill_valve = 0;
    requested->remote_vent_valve = 0;

    //open the rocket vent valve
    requested->run_tank_valve = 1;

    //do not touch the injector valve. Keep it where it is
    requested->injector_valve = get_current_state()->injector_valve;

    //don't move the linear actuator
    requested->linear_actuator = get_current_state()->linear_actuator;

    //turn off ignition
    requested->ignition_power = 0;
    requested->ignition_select = 0;


    //apply that state
    apply_state();
}

void tower_handle_vent_update(sensor_data_t *update)
{
    //store the pressure in the daq singleton
    if(update->pressure <= 999)
        global_current_daq.pressure3 = update->pressure;
    else
        global_current_daq.pressure3 = update->pressure;
}

void tower_handle_inj_update(sensor_data_t *update)
{
    //do nothing. For now.
}

//global for how long it's been since the output log was flushed
//to the SD card
unsigned long global_time_last_output_flush = 0;
const unsigned long global_output_flush_interval = 10000;
//global for how long it's been since we logged daq values
unsigned long global_time_last_logged_daq = 0;
const unsigned long global_time_between_daq_logs = 7000;
