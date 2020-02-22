#include "injector.h"
#include "Arduino.h"
#include "tower_pin_defines.h"
#include "tower_globals.h"

static enum{
  OFF,
  ARMED,
  POWERED,
  UNPOWERED
} fuel_injector_state = OFF;

static unsigned long time_of_fuel_injector_open = 0;
static unsigned long time_of_fuel_injector_powerdown = 0;
static unsigned long time_of_fuel_injector_powerup = 0;

void fuel_injector_refresh(){
  if(get_global_current_daq()->fuel_injector_valve_lsw_open){
    fuel_injector_state = OFF;
  }
  switch(fuel_injector_state){
    case OFF:
      //do nothing
      break;

    case ARMED:
      if(millis() >= time_of_fuel_injector_open){
        digitalWrite(PIN_FUEL_INJECTOR_VALVE_POWER, HIGH);
        digitalWrite(PIN_FUEL_INJECTOR_VALVE_SELECT, LOW);
        fuel_injector_state = POWERED;
        time_of_fuel_injector_powerdown = millis() + FUEL_INJECTOR_POWERED_TIME;
      }
      break;
    case POWERED:
      if(millis() >= time_of_fuel_injector_powerdown){  // time to turn off
        digitalWrite(PIN_FUEL_INJECTOR_VALVE_POWER, LOW);
        //digitalWrite(PIN_FUEL_INJECTOR_VALVE_SELECT, HIGH);
        time_of_fuel_injector_powerup = millis() + FUEL_INJECTOR_UNPOWERED_TIME;  //set when we should turn the motor back on
        fuel_injector_state = UNPOWERED;        
      }
      break;
    case UNPOWERED:
      if(millis() >= time_of_fuel_injector_powerup){  // time to turn back on
        digitalWrite(PIN_FUEL_INJECTOR_VALVE_POWER, HIGH);
        //digitalWrite(PIN_FUEL_INJECTOR_VALVE_SELECT, LOW);
        time_of_fuel_injector_powerdown = millis() + FUEL_INJECTOR_POWERED_TIME;  //set when we should turn the motor off
        fuel_injector_state = POWERED;        
      }
      break;

     default:
      break;
    
  }
}

void open_fuel_injector(){
  fuel_injector_state = ARMED;
  time_of_fuel_injector_open = millis() + OPEN_DELAY;

}

void close_fuel_injector(){
      digitalWrite((uint8_t) PIN_FUEL_INJECTOR_VALVE_POWER, HIGH);
      digitalWrite((uint8_t) PIN_FUEL_INJECTOR_VALVE_SELECT, HIGH);
      fuel_injector_state = OFF;

}
