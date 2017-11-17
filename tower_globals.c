#include "tower_globals.h"
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
		if(global_current_state.run_tank_valve){
			//open the run_tank_valve
		} else {
			//close the run_tank_valve
		}
	}
	if(global_requested_state.linear_actuator != global_current_state.linear_actuator){
		//we need to change the linear_actuator to what requested wants
		global_current_state.linear_actuator = global_requested_state.linear_actuator;
		if(global_current_state.linear_actuator){
			//retract the linear_actuator
		} else {
			//extend the linear_actuator
		}
	}
	if(global_requested_state.ignition_power != global_current_state.ignition_power){
		//we need to change the ignition_power to what requested wants
		global_current_state.ignition_power = global_requested_state.ignition_power;
		if(global_current_state.ignition_power){
			//open the ignition_power
		} else {
			//close the ignition_power
		}
	}
	if(global_requested_state.ignition_select != global_current_state.ignition_select){
		//we need to change the ignition_select to what requested wants
		global_current_state.ignition_select = global_requested_state.ignition_select;
		if(global_current_state.ignition_select){
			//open the ignition_select
		} else {
			//close the ignition_select
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

	//close the valves. This is the safest startup state
	digitalWrite((uint8_t) PIN_REMOTEFILL_POWER, HIGH);
	digitalWrite((uint8_t) PIN_REMOTEFILL_SELECT, HIGH); //select pin going high should set it to close, if it's wired right
	digitalWrite((uint8_t) PIN_REMOTEVENT_POWER, HIGH);
	digitalWrite((uint8_t) PIN_REMOTEVENT_SELECT, HIGH); //select pin going high should set it to close, if it's wired right
	

}
