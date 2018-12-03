#include "client_globals.h"
#include "client_pin_defines.h"
#include "shared_types.h"
#include "Arduino.h"

static actuator_state_t global_button_state, global_tower_state;
static daq_holder_t global_current_daq = {
    .pressure1 = 999,
    .pressure2 = 999,
    .pressure3 = 999,
    .rocket_mass = 0xFFFF,
    .ign_pri_current = 0xFFFF,
    .ign_sec_current = 0xFFFF,
    .rfill_lsw_open = 0,
    .rfill_lsw_closed = 0,
    .rvent_lsw_open = 0,
    .rvent_lsw_closed = 0,
    .rocketvent_lsw_open = 0,
    .rocketvent_lsw_closed = 0,
    .injectorvalve_lsw_open = 0,
    .injectorvalve_lsw_closed = 0,
    .linac_lsw_extend = 0,
    .linac_lsw_retract = 0
};

typedef uint8_t button_t;
static struct {
    button_t remotefill;
    button_t remotevent;
    button_t rocketvalve;
    button_t linactuator;
    button_t injector;
    button_t ignition_pri;
    button_t ignition_sec;
    button_t ignition_fire;
} button_debounce[DEBOUNCE_WIDTH];
static uint8_t button_debounce_index = 0;

//boolean to track whether we need to recalculate global button state before
//handing it back to the caller
static uint8_t global_button_state_tainted = 1;
actuator_state_t* get_button_state(){
    if(global_button_state_tainted) {
        //recalculate button state. We do calculations here for
        //software debouncing purposes
        button_t remotefill = 1;
        button_t remotevent = 1;
        button_t rocketvalve = 1;
        button_t linactuator = 1;
        button_t injector = 1;
        button_t ignition_pri = 1;
        button_t ignition_sec = 1;
        button_t ignition_fire = 1;
        for(int i = 0; i < DEBOUNCE_WIDTH; i++) {
            //each button is only considered active (high)
            //if all readings in the past DEBOUNCE width
            //readings were active
            remotefill &= button_debounce[i].remotefill;
            remotevent &= button_debounce[i].remotevent;
            rocketvalve &= button_debounce[i].rocketvalve;
            linactuator &= button_debounce[i].linactuator;
            injector &= button_debounce[i].injector;
            ignition_pri &= button_debounce[i].ignition_pri;
            ignition_sec &= button_debounce[i].ignition_sec;
            ignition_fire &= button_debounce[i].ignition_fire;
        }

        //now decode the debounced button states into an actuator_state_t
        global_button_state.remote_fill_valve =
            remotefill ? 1 : 0;
        global_button_state.remote_vent_valve =
            remotevent ? 1 : 0;
        global_button_state.run_tank_valve =
            rocketvalve ? 1 : 0;
        global_button_state.injector_valve =
            injector ? 1 : 0;
        global_button_state.linear_actuator =
            linactuator ? 1 : 0;

        //by default, ignition relays are both off
        global_button_state.ignition_power = global_button_state.ignition_select = 0;
        if(ignition_fire) {
            if(ignition_pri && !ignition_sec) {
                global_button_state.ignition_power = 1;
            } else if ( !ignition_pri && ignition_sec) {
                global_button_state.ignition_power = 1;
                global_button_state.ignition_select = 1;
            } else {
                //either both missile switches are thrown, or neither
                //either way, don't turn on either of the relays
            }
        }

        global_button_state_tainted = 0;
    }
    return &global_button_state;
}

actuator_state_t* get_tower_state(){
    return &global_tower_state;
}

daq_holder_t* get_tower_daq(){
    return &global_current_daq;
}


void read_all_buttons(){
    button_debounce[button_debounce_index].remotefill =
        digitalRead(PIN_SWITCH_REMOTEFILL) == HIGH;
    button_debounce[button_debounce_index].remotevent =
        digitalRead(PIN_SWITCH_REMOTEVENT) == HIGH;
    button_debounce[button_debounce_index].rocketvalve =
        digitalRead(PIN_SWITCH_ROCKETVALVE) == HIGH;
    button_debounce[button_debounce_index].linactuator =
        digitalRead(PIN_SWITCH_LINACTUATOR) == HIGH;
    button_debounce[button_debounce_index].injector =
        digitalRead(PIN_SWITCH_INJECTOR) == HIGH;
    button_debounce[button_debounce_index].ignition_pri =
        digitalRead(PIN_SWITCH_IGNITION_PRI) == HIGH;
    button_debounce[button_debounce_index].ignition_sec =
        digitalRead(PIN_SWITCH_IGNITION_SEC) == HIGH;
    //fire is active low
    button_debounce[button_debounce_index].ignition_fire =
        digitalRead(PIN_SWITCH_IGNITION_FIRE) == LOW;

    if( (++button_debounce_index) >= DEBOUNCE_WIDTH )
        button_debounce_index = 0;

    //mark boolean to
    global_button_state_tainted = 1;
}

void init_buttons(){
    pinMode(PIN_SWITCH_REMOTEFILL, INPUT);
    pinMode(PIN_SWITCH_REMOTEVENT, INPUT);
    pinMode(PIN_SWITCH_ROCKETVALVE, INPUT);
    pinMode(PIN_SWITCH_LINACTUATOR, INPUT);
    pinMode(PIN_SWITCH_INJECTOR, INPUT);
    pinMode(PIN_SWITCH_IGNITION_PRI, INPUT);
    pinMode(PIN_SWITCH_IGNITION_SEC, INPUT);
    pinMode(PIN_SWITCH_IGNITION_FIRE, INPUT_PULLUP);

    //zero out all the buttons
    memset(&button_debounce, 0, sizeof(button_debounce));

    //LEDs. Turn on the red one first
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    digitalWrite(PIN_LED_RED, HIGH);
    digitalWrite(PIN_LED_GREEN, LOW);
}

static int led_state = 0;
void set_radio_status(int state){

    if(state == led_state)
        return;
    //If state is true, then turn on green led
    if((led_state = state)) {
        digitalWrite(PIN_LED_GREEN, HIGH);
        digitalWrite(PIN_LED_RED, LOW);
    } else {
        digitalWrite(PIN_LED_GREEN, LOW);
        digitalWrite(PIN_LED_RED, HIGH);
    }
    //update led_state
    led_state = state;
}


//globals for how long it's been since we've made requests to the tower
unsigned long global_time_last_tower_state_req = 0;
const unsigned long global_tower_update_interval = 1000; //request every second
const unsigned long global_radio_timeout = 5000; //we've lost radio contact
unsigned long global_time_last_tower_daq_req = 0;
const unsigned long global_tower_daq_update_interval = 1000; //request daq every 1 seconds
//how often to flush the buffered output to the SD card
unsigned long global_time_last_output_flush = 0;
const unsigned long global_output_flush_interval = 30000; //every 30 seconds

unsigned long global_time_last_logged_daq = 0;
