#ifndef NODEIO_IOIO_H
#define NODEIO_IOIO_H

#ifdef __cplusplus
extern "C" {
#endif
#define NODE_GROUND
#include <stdint.h>

/* Nodeio.ioio is the name of the local area network formed by two xbees
 * on or around the rocket, one being in the injector valve section (which
 * handles rocketCAN), and one in the tower side RLCS box (which is named
 * ground).
 *
 * Nodeio.ioio has three goals:
 *  - Open the injector valve when the operator says so
 *  - Open the vent valve when the operator says so
 *  - send sensor data from both inj and vent back to the operator
 *
 * Everything of importance is held in the system_state type
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
    VALVE_OPEN = 0,
    VALVE_CLOSED,
    NOTHING,
    VALVE_ILLEGAL,
} nio_actuator_state;

//copied from RocketCAN
typedef struct {
    uint16_t tank_pressure;
    uint8_t num_boards_connected;
    nio_actuator_state injector_valve_state;
    nio_actuator_state vent_valve_state;
    bool bus_is_powered;
    bool any_errors_detected;
} system_state;

//initialization function. Sets up Serial communication
void nio_init(void);

//call this function every loop. It checks for new packets, and handles
//incoming commands if need be (opening and closing the valve as needed)
void nio_refresh(void);

//helpers to set which position a valve should be in
void nio_set_vent_desired(nio_actuator_state);
void nio_set_inj_desired(nio_actuator_state);
void nio_depower_bus(void);
void nio_power_bus(void);

#ifdef __cplusplus
}
#endif

#endif
