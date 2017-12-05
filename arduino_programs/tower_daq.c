#include "tower_daq.h"
#include "shared_types.h"
#include "tower_pin_defines.h"
#include "Arduino.h"

//used for holding intermediate values
static struct {
    //all analog daq values range from 0 to 1023 (10 bit ADC)
    //so they are stored in 16 bit unsigneds
    uint16_t mass;
    uint16_t pressure1;
    uint16_t pressure2;
    uint16_t curr_ignition_pri;
    uint16_t curr_ignition_sec;
    uint16_t curr_remotefill_opn;
    uint16_t curr_remotefill_cls;
    uint16_t curr_remotevent_opn;
    uint16_t curr_remotevent_cls;
    uint16_t curr_linac_ext;
    uint16_t curr_linac_ret;
    //all limit switches are digital values (either 1 or 0_
    //these could be packed into a bit field, but I'm not 
    //at all worried about space, so am currently using uint8_t's
    uint8_t lsw_remotefill_opn;
    uint8_t lsw_remotefill_cls;
    uint8_t lsw_remotevent_opn;
    uint8_t lsw_remotevent_cls;
    uint8_t lsw_linac_ext;
    uint8_t lsw_linac_ret;
} window_holder[WINDOW_WIDTH];


void init_daq_pins() {
    pinMode(PIN_DAQ_PRESSURE1, INPUT);
    pinMode(PIN_DAQ_PRESSURE2, INPUT);
    pinMode(PIN_DAQ_MASS, INPUT);
    pinMode(PIN_CURRENT_IGNITION_PRI, INPUT);
    pinMode(PIN_CURRENT_IGNITION_SEC, INPUT);
    pinMode(PIN_CURRENT_REMOTEFILL_OPN, INPUT);
    pinMode(PIN_CURRENT_REMOTEFILL_CLS, INPUT);
    pinMode(PIN_CURRENT_REMOTEVENT_OPN, INPUT);
    pinMode(PIN_CURRENT_REMOTEVENT_CLS, INPUT);
    pinMode(PIN_CURRENT_LINAC_EXT, INPUT);
    pinMode(PIN_CURRENT_LINAC_RET, INPUT);
    pinMode(PIN_LIMITSW_REMOTEFILL_OPN, INPUT);
    pinMode(PIN_LIMITSW_REMOTEFILL_CLS, INPUT);
    pinMode(PIN_LIMITSW_REMOTEVENT_OPN, INPUT);
    pinMode(PIN_LIMITSW_REMOTEVENT_CLS, INPUT);
    pinMode(PIN_LIMITSW_LINAC_EXT, INPUT);
    pinMode(PIN_LIMITSW_LINAC_RET, INPUT);

    //set all the values in our window holder to 0
    memset(0, &window_holder, sizeof(window_holder));
}

static int window_holder_index = 0;
void read_daq_pins() {
    //read all analog values into window holder
    window_holder[window_holder_index].mass = 
        analogRead(PIN_DAQ_MASS);
    window_holder[window_holder_index].pressure1 = 
        analogRead(PIN_DAQ_PRESSURE1);
    window_holder[window_holder_index].pressure2 = 
        analogRead(PIN_DAQ_PRESSURE2);
    window_holder[window_holder_index].curr_ignition_pri = 
        analogRead(PIN_CURRENT_IGNITION_PRI);
    window_holder[window_holder_index].curr_ignition_sec = 
        analogRead(PIN_CURRENT_IGNITION_SEC);
    window_holder[window_holder_index].curr_remotefill_opn = 
        analogRead(PIN_CURRENT_REMOVEFILL_OPN);
    window_holder[window_holder_index].curr_remotefill_cls = 
        analogRead(PIN_CURRENT_REMOVEFILL_CLS);
    window_holder[window_holder_index].curr_remotevent_opn = 
        analogRead(PIN_CURRENT_REMOVEVENT_OPN);
    window_holder[window_holder_index].curr_remotevent_cls = 
        analogRead(PIN_CURRENT_REMOVEVENT_CLS);
    window_holder[window_holder_index].curr_linac_ext = 
        analogRead(PIN_CURRENT_LINAC_EXT);
    window_holder[window_holder_index].curr_linac_ret = 
        analogRead(PIN_CURRENT_LINAC_RET);

    //now read in all the digital values
    window_holder[window_holder_index].lsw_remotefill_opn =
        digitalRead(PIN_LIMITSW_REMOTEFILL_OPN);
    window_holder[window_holder_index].lsw_remotefill_cls =
        digitalRead(PIN_LIMITSW_REMOTEFILL_CLS);
    window_holder[window_holder_index].lsw_remotevent_opn =
        digitalRead(PIN_LIMITSW_REMOTEVENT_OPN);
    window_holder[window_holder_index].lsw_remotevent_cls =
        digitalRead(PIN_LIMITSW_REMOTEVENT_CLS);
    window_holder[window_holder_index].lsw_linac_ext =
        digitalRead(PIN_LIMITSW_LINAC_EXT);
    window_holder[window_holder_index].lsw_linac_ret =
        digitalRead(PIN_LIMITSW_LINAC_RET);

    //increment window counter, check if it's bigger than the window,
    //if so, set it to 0
    if(++window_holder_index > WINDOW_WIDTH)
        window_holder_index = 0;
}



void compute_daq_values(daq_holder_t* output) {
    //need 

}
