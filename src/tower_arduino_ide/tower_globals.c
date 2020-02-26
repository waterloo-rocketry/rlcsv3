#include "tower_globals.h"
#include "tower_daq.h"
#include "tower_pin_defines.h"
#include "nodeio.ioio.h"
#include "sd_handler.h"
#include "linac.h"
#include "injector.h"
#include "Arduino.h"

static actuator_state_t global_requested_state;
static actuator_state_t global_current_state = {
    .remote_fill_valve = 0,
    .remote_vent_valve = 0,
    .run_tank_valve = 1,
    .injector_valve = 0,
    .linear_actuator = 0,
    .ignition_power = 0,
    .ignition_select = 0,
    .ox_pres_valve = 0,
    .fuel_pres_valve = 0
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

    if(global_requested_state.ox_pres_valve != global_current_state.ox_pres_valve){
        //we need to change the ox_pres_valve to what requested wants
        global_current_state.ox_pres_valve = global_requested_state.ox_pres_valve;
        if(global_current_state.ox_pres_valve){
            //open the ox_pres_valve
            digitalWrite((uint8_t) PIN_OX_PRES_VALVE_POWER, HIGH);
            digitalWrite((uint8_t) PIN_OX_PRES_VALVE_SELECT, LOW);
        } else {
            //close the ox_pres_valve
            digitalWrite((uint8_t) PIN_OX_PRES_VALVE_POWER, HIGH);
            digitalWrite((uint8_t) PIN_OX_PRES_VALVE_SELECT, HIGH);
        }
    }

    if (global_requested_state.fuel_pres_valve != global_current_state.fuel_pres_valve){
        //we need to change the fuel_pres_valve to what requested wants
        global_current_state.fuel_pres_valve = global_requested_state.fuel_pres_valve;
        if (global_current_state.fuel_pres_valve){
            //open the fuel_pres_valve
            digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_POWER, HIGH);
            digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_SELECT, LOW);
        } else {
            //close the fuel_pres_valve
            digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_POWER, HIGH);
            digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_SELECT, HIGH);
        } // else
    } // if

    global_current_state.run_tank_valve = global_requested_state.run_tank_valve;
    //tell nodeio.ioio that we want the vent to change
    if(global_requested_state.run_tank_valve){
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

        //open the injector valves
        digitalWrite((uint8_t) PIN_OX_INJECTOR_VALVE_POWER, HIGH);
        digitalWrite((uint8_t) PIN_OX_INJECTOR_VALVE_SELECT, LOW);
        open_fuel_injector();
    }
    else {
        nio_set_inj_desired(VALVE_CLOSED);
        
        //close the injector valves
        digitalWrite((uint8_t) PIN_OX_INJECTOR_VALVE_POWER, HIGH);
        digitalWrite((uint8_t) PIN_OX_INJECTOR_VALVE_SELECT, HIGH);
        close_fuel_injector();
    }

    if(global_requested_state.linear_actuator != global_current_state.linear_actuator){
        //we need to change the linear_actuator to what requested wants
        if(global_current_state.linear_actuator){
            //retract the linear_actuator
            if(linac_retract())
                global_current_state.linear_actuator = global_requested_state.linear_actuator;
        } else {
            //extend the linear_actuator
            if(linac_extend())
                global_current_state.linear_actuator = global_requested_state.linear_actuator;
        }
    }

    if(global_requested_state.ignition_power != global_current_state.ignition_power){
        //we need to change the ignition_power to what requested wants
        global_current_state.ignition_power = global_requested_state.ignition_power;
        if(global_current_state.ignition_power){
            //decide whether to write to primary or secondary ignition
            if(global_requested_state.ignition_select) {
                //write to secondary
                digitalWrite((uint8_t) PIN_IGNITION_POWER, HIGH);
                digitalWrite((uint8_t) PIN_IGNITION_SELECT, LOW);
            } else {
                //write to primary
                digitalWrite((uint8_t) PIN_IGNITION_POWER, HIGH);
                digitalWrite((uint8_t) PIN_IGNITION_SELECT, HIGH);

            }
        } else {
            //remove power from ignition circuit
            digitalWrite((uint8_t) PIN_IGNITION_POWER, LOW);
        }
    }

    if(global_requested_state.ignition_select != global_current_state.ignition_select){
        //we need to change the ignition_select to what requested wants
        global_current_state.ignition_select = global_requested_state.ignition_select;
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
    pinMode(PIN_OX_PRES_VALVE_POWER, OUTPUT);
    pinMode(PIN_OX_PRES_VALVE_SELECT, OUTPUT);
    pinMode(PIN_FUEL_PRES_VALVE_POWER, OUTPUT);
    pinMode(PIN_FUEL_PRES_VALVE_SELECT, OUTPUT);

    pinMode(PIN_IGNITION_POWER, OUTPUT);
    pinMode(PIN_IGNITION_SELECT, OUTPUT);
    pinMode(PIN_OX_INJECTOR_VALVE_POWER, OUTPUT);
    pinMode(PIN_OX_INJECTOR_VALVE_SELECT, OUTPUT);
    pinMode(PIN_FUEL_INJECTOR_VALVE_POWER, OUTPUT);
    pinMode(PIN_FUEL_INJECTOR_VALVE_SELECT, OUTPUT);
    
    //close the valves. This is the safest startup state
    //fill valve
    digitalWrite((uint8_t) PIN_REMOTEFILL_POWER, HIGH);
    digitalWrite((uint8_t) PIN_REMOTEFILL_SELECT, HIGH); //select pin going high should set it to close, if it's wired right

    //vent valve
    digitalWrite((uint8_t) PIN_REMOTEVENT_POWER, HIGH);
    digitalWrite((uint8_t) PIN_REMOTEVENT_SELECT, HIGH);

    // oxidizer pressurant valve
    digitalWrite((uint8_t) PIN_OX_PRES_VALVE_POWER, HIGH);
    digitalWrite((uint8_t) PIN_OX_PRES_VALVE_SELECT, HIGH);

    // fuel pressurant valve
    digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_POWER, HIGH);
    digitalWrite((uint8_t) PIN_FUEL_PRES_VALVE_SELECT, HIGH);

    //run tank valve
    //TODO, figure out how the run tank valve is going to work
    //likely involve a serial link to another arduino
    //I don't think this should be here, we have RocketCAN - Zach 2020-02-20

    linac_init();

    //ignition, set to off by default
    digitalWrite((uint8_t) PIN_IGNITION_POWER, LOW);
    digitalWrite((uint8_t) PIN_IGNITION_SELECT, LOW);

    //turn off the pin 13 LED
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

//called when client hasn't told us to do anything for a while
//assume comms are entirely lost, close all the valves (except the
//rocket tank vent valve)
void goto_safe_mode()
{
    //take the current requested state, set it to the safest possible
    //state, and then call apply_state
    actuator_state_t* requested = get_requested_state();

    //close fill
    requested->remote_fill_valve = 0;
    //open vent
    requested->remote_vent_valve = 1;
    //close pressurant
    requested->ox_pres_valve = 0;
    requested->fuel_pres_valve = 0;

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

//global for how long it's been since the output log was flushed
//to the SD card
unsigned long global_time_last_output_flush = 0;
const unsigned long global_output_flush_interval = 10000;
//global for how long it's been since we logged daq values
unsigned long global_time_last_logged_daq = 0;
const unsigned long global_time_between_daq_logs = 1000;
