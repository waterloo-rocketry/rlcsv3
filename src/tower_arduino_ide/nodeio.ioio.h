#ifndef NODEIO_IOIO_H
#define NODEIO_IOIO_H

#ifdef __cplusplus
extern "C" {
#endif
#define NODE_GROUND
#include <stdint.h>

/* Nodeio.ioio is the name of the local area network formed by three xbees
 * on or around the rocket, one being in the injector valve section (which
 * is named inj), one in the vent section (which is named vent), and one in
 * the tower side RLCS box (which is named ground).
 *
 * Nodeio.ioio has three goals:
 *  - Open the injector valve when the operator says so
 *  - Open the vent valve when the operator says so
 *  - send sensor data from both inj and vent back to the operator
 *
 * The sensor data is held in a sensor_data_t. Leave values unchanged if they
 * aren't needed, send them with nodeioio_send_sensor_data as often as you want.
 *
 * All actuator control is handled in nodeio_ioio_refresh. It currently assumes
 * that the valve is closed by setting pin pin_valve_closed high and the other
 * pin low (is that as desired?). Set this up by passing the pin numbers to the
 * init function at program startup.
 */

//different states that the valve can be in. Nothing
//means that the valve shouldn't be driven at all, VALVE_OPEN
//and VALVE_CLOSED are hopefully self explanatory, and
//VALVE_ILLEGAL, if read from the valve, mean that both limit
//switches are depressed simultaneously (should not happen).
//writing VALVE_ILLEGAL to the injector valve should cause the
//injector valve to open as little as possible (as a secondary
//emergency vent procedure). Do not write VALVE_ILLEGAL to the
//vent valve, it doesn't mean anything.
typedef enum {
    NOTHING,
    VALVE_OPEN,
    VALVE_CLOSED,
    VALVE_ILLEGAL,
} nio_actuator_state;

//how to identify whether we're talking about the injector valve or vent valve
typedef enum {
    NIO_INJECTOR_VALVE,
    NIO_VENT_VALVE,
} nio_valve_identifier;

#define SENSOR_DATA_LENGTH (2+(NUM_THERMISTORS))
typedef struct {
    uint16_t pressure;
    nio_actuator_state read_valve_state;
    nio_valve_identifier valve_id;
} sensor_data_t;


#define MOSFET_SWITCH_TIME_MS 150
//initialization function. Sets up Serial communication
void nio_init(void);

//call this function every loop. It checks for new packets, and handles
//incoming commands if need be (opening and closing the valve as needed)
void nio_refresh(void);

//helpers to set which position a valve should be in
void nio_set_vent_desired(nio_actuator_state);
void nio_set_inj_desired(nio_actuator_state);

#ifdef __cplusplus
}
#endif

#endif
