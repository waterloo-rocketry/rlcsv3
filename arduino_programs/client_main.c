#include "shared_types.h"
#include "client_fsm.h"
#include "client_globals.h"
#include "radio_comms.h"

void setup(){

}

void loop(){
    for(;;){
        //check for inputs from radio
        while(xbee_bytes_available()){
            //update FSM, which does the command processing
            push_radio_char(xbee_get_byte());
        }
        //read all the buttons/inputs, store in a global button state
        read_all_buttons();

        //check if button state matches last received tower state
        if (! actuator_state_equals(get_button_state(), get_tower_state())){
            //this function ensures enough time passes between each sent request
            radio_send_state_command(get_button_state());
        }

        //update the LCD
        update_lcd(&tower_daq);

        //check how long since we received tower state
        if (millis() - global_time_last_tower_state_rec > global_tower_update_interval){
            radio_request_state_update()
        }
    }
}
