#include "shared_types.h"

//using rfc 4648 base 64. Yes there's probably a library for this.
char fromBase64(char base64){
    if ( base64 >= 'A' && base64 <= 'Z' ) {
        //we need to map 'A' (ascii value 65) to 0. So subtract 65
        base64 -= 65;
    } else if (base64 >= 'a' && base64 <= 'z') {
        //we need to map 'a' (ascii value 97) to 26. So subtract 71
        base64 -= 71;
    } else if (base64 >= '0' && base64 <= '9') {
        //we need to map '0' (ascii value 48) to 52. So add 4
        base64 += 4;
    } else if (base64 == '+') {
        //we need to map '+' (ascii value 43) to 62. So add 19
        base64 += 19;
    } else if (base64 == '/') {
        //we need to map '/' (ascii value 47) to 63. so add 16
        base64 += 16;
    } else {
        //we have failed. So return -1
        return -1;
    }
    return base64;
}
char toBase64(char binary){
    if (binary >= 0 && binary <= 25) {
        //map to 'A' (ascii value 65). So add 65
        binary += 65;
    } else if (binary >= 26 && binary <= 51) {
        //map to 'a' (ascii value 97). So add 71
        binary += 71;
    } else if (binary >= 52 && binary <= 61) {
        //map to '0' (ascii value 48). So subtract 4
        binary -= 4;
    } else if (binary == 62) {
        //map to '+' (ascii value 43). So subtract 19
        binary -= 19;
    } else if (binary == 63) {
        //map to '/' (ascii value 47). So subtract 16
        binary -= 16;
    } else {
        //we have failed. So return -1
        return -1;
    }
    return binary;
}

//we need 64 different states. So these 2 functions use the RFC 4648
//base-64 alphabet. A=0,Z=25,a=26,0=52,9=61,+=62,/=63
int convert_radio_to_state(actuator_state_t* state, char binary)
{
    if ( (binary = fromBase64(binary)) < 0)
        //we did not receive a valid state. So return 0
        return 0;
    //if ignition power is on, then bit 7 is ignition select
    //if ignition power is off, then bit 7 is remote fill valve
    //if ignition is running, then remote fill valve must be closed
    state->injector_valve = ((binary & 1) != 0);
    state->remote_vent_valve = ((binary & 2) != 0);
    state->run_tank_valve    = ((binary & 4) != 0);
    state->linear_actuator   = ((binary & 8) != 0);
    state->ignition_power    = ((binary & 16) != 0);
    if(state->ignition_power){
        state->ignition_select   = ((binary & 32) != 0);
        state->remote_fill_valve = 0;
    } else {
        state->ignition_select = 0;
        state->remote_fill_valve = ((binary & 32) != 0);
    }
    return 1;
}

int convert_state_to_radio(const actuator_state_t* state, char* binary) 
{
    *binary = 0;
    *binary += state->injector_valve ? 1 : 0;
    *binary += state->remote_vent_valve ? 2 : 0;
    *binary += state->run_tank_valve    ? 4 : 0;
    *binary += state->linear_actuator   ? 8 : 0;
    *binary += state->ignition_power    ? 16 : 0;
    if(state->ignition_power){
        *binary += state->ignition_select   ? 32 : 0;
    } else {
        *binary += state->remote_fill_valve ? 32 : 0;
    }

    if ( (*binary = toBase64(*binary)) < 0)
        return 0; //we do this on failure
    return 1;
}

//returns 1 if they're the same, else returns 0
int actuator_compare(const actuator_state_t* s, const actuator_state_t* q)
{
    return  s->remote_fill_valve == q->remote_fill_valve &&
            s->remote_vent_valve == q->remote_vent_valve &&
            s->run_tank_valve == q->run_tank_valve &&
            s->injector_valve == q->injector_valve &&
            s->linear_actuator == q->linear_actuator &&
            s->ignition_power == q->ignition_power &&
            s->ignition_select == q->ignition_select;
}

//these functions could easily be changed to make them more efficient
//TODO I'm pretty sure you can decrease DAQ_RADIO_LEN from 17 to 10 by packing the three-digit values down
//That involves some bit level fuckery, so I'll leave that as an exercise for later
int convert_radio_to_daq(daq_holder_t* daq, const daq_radio_value_t* radio){
    //step 1: convert the first two bytes from radio to pressure1
    daq->pressure1 = fromBase64(radio->data[1]) << 5 |
        fromBase64(radio->data[0]);
    //step 2, do the second two bytes into pressure2
    daq->pressure2 = fromBase64(radio->data[3]) << 5 |
        fromBase64(radio->data[2]);
    //step 3, do the third two bytes into pressure3
    daq->pressure3 = fromBase64(radio->data[5]) << 5 |
        fromBase64(radio->data[4]);
    //step 4, that same thing but for rocket_mass
    daq->rocket_mass = fromBase64(radio->data[7]) << 5|
        fromBase64(radio->data[6]);
    //step 5, now for ign_pri_current
    daq->ign_pri_current = fromBase64(radio->data[9]) << 5 |
        fromBase64(radio->data[8]);
    //step 6: now for ign_sec_current
    daq->ign_sec_current = fromBase64(radio->data[11]) << 5 |
        fromBase64(radio->data[10]);
    //step 6: now let's do some binary stuff. convert byte 15 from base64
    char first_bitfield = fromBase64(radio->data[12]);
    char second_bitfield = fromBase64(radio->data[13]);
    if (first_bitfield < 0 || second_bitfield < 0)
        return 0; //we received an incorrect state

    daq->rfill_lsw_open      =   (first_bitfield & 32) != 0;
    daq->rfill_lsw_closed    =   (first_bitfield & 16) != 0;
    daq->rvent_lsw_open      =   (first_bitfield & 8) != 0;
    daq->rvent_lsw_closed    =   (first_bitfield & 4) != 0;
    daq->linac_lsw_extend    =   (first_bitfield & 2) != 0;
    daq->linac_lsw_retract   =   (first_bitfield & 1) != 0;

    daq->injector_valve_state     = static_cast<valve_state_t>((second_bitfield & 0b110000) >> 4);
    daq->rocketvent_valve_state   = static_cast<valve_state_t>((second_bitfield & 0b1100) >> 2);

    return 1;
}

//this does not check array length, so please pay attention to what you pass this
static void convert_uint16_to_2dig(uint16_t input, char* output){
    if (input > 999)
        input = 999;
    //it's impossible for input to be more than 10 bits
    output[0] = toBase64(input & 0b11111);
    output[1] = toBase64((input >> 5) & 0b11111);
}

int convert_daq_to_radio(const daq_holder_t* daq, daq_radio_value_t* radio){
    //this probably isn't safe, TODO, do some sanity checking here
    convert_uint16_to_2dig(daq->pressure1, radio->data);
    convert_uint16_to_2dig(daq->pressure2, radio->data + 2);
    convert_uint16_to_2dig(daq->pressure3, radio->data + 4);
    convert_uint16_to_2dig(daq->rocket_mass, radio->data + 6);
    convert_uint16_to_2dig(daq->ign_pri_current, radio->data + 8);
    convert_uint16_to_2dig(daq->ign_sec_current, radio->data + 10);

    char first_bitfield = 0, second_bitfield = 0;

    first_bitfield += daq->rfill_lsw_open? 32 : 0;
    first_bitfield += daq->rfill_lsw_closed ? 16 : 0;
    first_bitfield += daq->rvent_lsw_open? 8 : 0;
    first_bitfield += daq->rvent_lsw_closed ? 4 : 0;
    first_bitfield += daq->linac_lsw_extend? 2 : 0;
    first_bitfield += daq->linac_lsw_retract ? 1 : 0;

    second_bitfield |= daq->injector_valve_state << 4;
    second_bitfield |= daq->rocketvent_valve_state << 2;

    first_bitfield = toBase64(first_bitfield);
    second_bitfield = toBase64(second_bitfield);
    if(first_bitfield < 0 || second_bitfield < 0)
        return 0;
    radio->data[12] = first_bitfield;
    radio->data[13] = second_bitfield;
    return 1;
}
