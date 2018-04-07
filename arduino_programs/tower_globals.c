#include "tower_globals.h"
#include "tower_daq.h"
#include "tower_pin_defines.h"
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
		//TODO, figure out how this run tank valve is supposed to work
		//Likely to involve a radio link to the rocket maybe?
	}

    if(global_requested_state.injector_valve != global_current_state.injector_valve){
        global_current_state.injector_valve = global_requested_state.injector_valve;
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
