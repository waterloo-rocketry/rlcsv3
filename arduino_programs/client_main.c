#include "shared_types.h"
#include "client_fsm.h"
#include "client_globals.h"
#include "radio_comms.h"
#include "SevSeg.h"
#include "Arduino.h"

void setup(){
    start_SevSeg();
}

extern unsigned long global_time_last_tower_state_req, global_time_last_tower_daq_req;
extern const unsigned long global_tower_update_interval, global_tower_daq_update_interval;
void loop(){
	//check for inputs from radio
	while(xbee_bytes_available()){
		//update FSM, which does the command processing
		push_radio_char(xbee_get_byte());
	}
	//read all the buttons/inputs, store in a global button state
	read_all_buttons();

	//check if button state matches last received tower state
	if (! actuator_compare(get_button_state(), get_tower_state())){
		//this function ensures enough time passes between each sent request
		client_push_state(get_button_state());
	}

	//update the LCD
	//update_lcd(get_tower_daq());

	//check how long since we received tower state

	if (millis() - global_time_last_tower_state_req > global_tower_update_interval){
		client_request_state();
	}

	//check how long since we received tower daq information
	if (millis() - global_time_last_tower_daq_req > global_tower_daq_update_interval){
		client_request_daq();
	}

    //put the last received tower state on seven seg
    char to_put_on_sevseg;
    if( convert_state_to_radio(get_tower_state(), &to_put_on_sevseg) ) {
        setNewNum_SevSeg( (uint8_t) to_put_on_sevseg );
    }
    refresh_SevSeg();
    
}
