#ifndef INJECTOR_H
#define INJECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#define OPEN_DELAY 250 //time between open comand, and beginning of opening, in ms
#define FUEL_INJECTOR_POWERED_TIME 30 //time the valve is on while moving
#define FUEL_INJECTOR_UNPOWERED_TIME 100 //time the valve is off while moving

void fuel_injector_refresh();
void open_fuel_injector();
void close_fuel_injector();

#ifdef __cplusplus
}
#endif

#endif  //compile guard
