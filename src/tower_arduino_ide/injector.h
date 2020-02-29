#ifndef INJECTOR_H
#define INJECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

void fuel_injector_refresh();
void ox_injector_refresh();
void open_fuel_injector();
void close_fuel_injector();
void open_ox_injector();
void close_ox_injector();

#ifdef __cplusplus
}
#endif

#endif  //compile guard
