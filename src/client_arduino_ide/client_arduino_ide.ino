#include "shared_types.h"
#include "client_fsm.h"
#include "client_globals.h"
#include "radio_comms.h"
#include "SevSeg.h"
#include "LCD.h"
#include "Arduino.h"
#include "sd_handler.h"


void setup()
{
    lcd_init();
    start_SevSeg();
    radio_init();
    init_buttons();
    sd_init();
    if(sd_active()){
        rlcslog("start of operations");
    }
}

extern unsigned long
        global_time_last_tower_state_req,
        global_time_last_tower_daq_req,
        global_time_last_output_flush;
extern const unsigned long
        global_tower_update_interval,
        global_tower_daq_update_interval,
        global_radio_timeout,
        global_output_flush_interval;

void loop()
{
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
  lcd_update(get_tower_daq());

  //check how long since we received tower state

  if (millis_offset() - global_time_last_tower_state_req > global_tower_update_interval){
    client_request_state();
  }

  //check how long since we received tower daq information
  if (millis_offset() - global_time_last_tower_daq_req > global_tower_daq_update_interval){
    client_request_daq();
  }


    //if it's been longer than some defined amount of time,
    //turn on the red led to say that it's been too long
    if (millis_offset() - global_time_last_tower_state_req > global_radio_timeout)
        set_radio_status(0);
    else
        set_radio_status(1);

    //refresh the seven segment display
    char button_for_sevseg;
    convert_state_to_radio(get_button_state(), &button_for_sevseg);
    setNewNum_SevSeg(fromBase64(button_for_sevseg));
    refresh_SevSeg();

    //log the current button state - doesn't write if no change
    if(sd_active){
       rlcslog_client_button(get_button_state());
    }

    //check how long it's been since we flushed the log
    if(millis() - global_time_last_output_flush > global_output_flush_interval){
        flush();
    }
}

