#include "LCD.h"
#include <LiquidCrystal.h>
#include <Arduino.h>
#include "client_pin_defines.h"

/* We have a 4x20 LCD to work with, we need to display the following data
 *
 *x fill tank pressure
 *x line pressure
 *x rocket mass
 *x run tank pressure
 *  battery voltages:
 *    RLCS client
 *    RLCS tower
 *    RocketCAN bus battery
 *    RocketCAN vent battery
 *  valve positions:
 *x   Fill
 *x   Line Vent
 *x   Tank Vent
 *x   Injector
 *x   Fill arm (kind of a valve)
 *x ignition currents (2)
 *
 *  Here's how we're going to lay all that out. The top row of the LCD
 *  will always contain the following text
 *  RF:___ RV:___ TV:___
 *
 *  These are the positions of the three most important valves, we always
 *  need to know what they are (remote fill, remote vent, and tank vent)
 *
 *  The next line will always display the following DAQ values, since they
 *  are the only time critical values (if we don't see them for 10 seconds,
 *  we are maybe fucked):
 *  IP:___ IS:___ PT:___
 *  (those are ignition primary current, ignition secondary current, and
 *  flight tank pressure)
 *
 *  The next line switches back and forth between the following DAQ values
 *  every 2 seconds (2 seconds on, 2 seconds off):
 *  IV:___ PS:___ M:____ and IV:___ PL:___ RD:___
 *  Those are, in order, injector valve, pressure in supply tank, rocket mass,
 *  injector valve again (it should always be onscreen), pressure in fill
 *  lines, and remote disconnect status
 *
 *  The fourth line alternates between battery voltages and error messages
 *  from rocketCAN. The battery voltages alternate back and forth between
 *  these two lines:
 *  BAT TA:_____TM:_____ and BAT FB:_____FV:_____
 *  those values are all in millivolts, the acronyms stand for "tower actuators",
 *  "tower main", "flight bus", and "flight vent".
 *
 *  whenever an error message from RocketCAN is available, a string
 *  like the following will marquee across the LCD
 *  "E_BOARD_FEARED_DEAD RADIO_BOARD $board_id E_BOARD_FEARED_DEAD"
 *  between every marqueed error message both battery voltage lines
 *  will be displayed in succession, to make sure no data is missed.
 *  Error messages will queue up, so make sure rocketCAN doesn't send
 *  too goddamn many.
 */

static LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4,
                         PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
void lcd_init()
{
    lcd.begin(20, 4);
    lcd.setCursor(2, 1);
    lcd.print("WAITING FOR DATA");
}

static void display_valves_line(unsigned char fill_open,
                                unsigned char fill_closed, unsigned char vent_open, unsigned char vent_closed,
                                valve_state_t rocket_vent_state);
static void display_currents_line(uint16_t pri_current, uint16_t sec_current,
                                  uint16_t rocket_tank_pressure);
static void display_mass_line(valve_state_t injector_state,
                              uint16_t fill_tank_pressure, uint16_t mass);
static void display_disconnect_line(valve_state_t injector_state,
                                    uint16_t fill_line_pressure, unsigned char linac_extend,
                                    unsigned char linac_retract);
static void display_ground_batt_line(uint16_t client_batt, uint16_t tower_batt);
static void display_rocket_batt_line(uint16_t flight_bus_batt,
                                     uint16_t flight_vent_batt);
static void marquee_current_error();
static void marquee_next_error();

//static variables we keep track of in order to show marquee error msgs
static bool currently_marqueeing_error = false;
static char buffer_to_marquee[10][20];
static uint8_t marquee_buffer_index = 0;
static uint8_t num_errors_queued = 0;
static long time_last_error_displayed = 0;

void lcd_update(daq_holder_t *input)
{
    //two of the LCD lines switch back and forth between two lines
    //every two seconds. We use this variable to keep track of which
    //line should be displayed at the current time
    static bool display_first_line = true;
    //timer to keep track of when to switch between lines
    static long time_last_line_switch = 0;
    //if we need to switch lines, do so
    if (millis() - time_last_line_switch > 2000) {
        display_first_line = !display_first_line;
        time_last_line_switch = millis();
    }


    //display the top line
    display_valves_line(input->rfill_lsw_open, input->rfill_lsw_closed,
                        input->rvent_lsw_open, input->rvent_lsw_closed,
                        input->rocketvent_valve_state);

    //display the second line
    display_currents_line(input->ign_pri_current, input->ign_sec_current,
                          input->pressure3);

    //display the third line
    if (display_first_line) {
        //the one with the rocket mass in it
        display_mass_line(input->injector_valve_state, input->pressure1,
                          input->rocket_mass);
    } else {
        //the one with the remote disconnect status
        display_disconnect_line(input->injector_valve_state, input->pressure2,
                                input->linac_lsw_extend,
                                input->linac_lsw_retract);
    }

    //this one's fun
    if (currently_marqueeing_error) {
        marquee_current_error();
    } else if (num_errors_queued != 0 &&
               millis() - time_last_error_displayed > 9000) {
        marquee_next_error();
    } else {
        if (display_first_line) {
            display_ground_batt_line(input->rlcs_actuator_batt_mv, input->rlcs_main_batt_mv);
        } else {
            display_rocket_batt_line(input->bus_batt_mv, input->vent_batt_mv);
        }
    }
}

void display_new_error(const char *error)
{
    if (num_errors_queued == 10)
        return;
    uint8_t write_index = (marquee_buffer_index + num_errors_queued ) % 10;
    strncpy(buffer_to_marquee[write_index], error, sizeof(buffer_to_marquee[0]));
    Serial.println(error);
    num_errors_queued++;
}

static void display_valves_line(unsigned char fill_open,
                                unsigned char fill_closed, unsigned char vent_open, unsigned char vent_closed,
                                valve_state_t rocket_vent_state)
{
    lcd.setCursor(0, 0);
    char line[21];
    snprintf(line, 21, "RF:%s RV:%s TV:%s",
             (fill_open && !fill_closed) ? "OPN" :
             (!fill_open && fill_closed) ? "CLS" : "UNK",
             (vent_open && !vent_closed) ? "OPN" :
             (!vent_open && vent_closed) ? "CLS" : "UNK",
             (rocket_vent_state == DAQ_VALVE_OPEN) ? "OPN" :
             (rocket_vent_state == DAQ_VALVE_CLOSED) ? "CLS" :
             (rocket_vent_state == DAQ_VALVE_UNK) ? "UNK" : "ILL");
    lcd.print(line);
}

static void display_currents_line(uint16_t pri_current, uint16_t sec_current,
                                  uint16_t rocket_tank_pressure)
{
    lcd.setCursor(0, 1);
    if (pri_current > 999)
        pri_current = 999;
    if (sec_current > 999)
        sec_current = 999;
    if (rocket_tank_pressure > 999)
        rocket_tank_pressure = 999;
    char line[21];
    snprintf(line, 21, "IP:%03u IS:%03u PT:%03u", pri_current, sec_current,
             rocket_tank_pressure);
    lcd.print(line);
}

static void display_mass_line(valve_state_t injector_state,
                              uint16_t fill_tank_pressure, uint16_t mass)
{
    lcd.setCursor(0, 2);
    if (fill_tank_pressure > 999)
        fill_tank_pressure = 999;
    char line[21];
    snprintf(line, 21, "IV:%s PS:%03u M:%04u",
             (injector_state == DAQ_VALVE_OPEN) ? "OPN" :
             (injector_state == DAQ_VALVE_CLOSED) ? "CLS" :
             (injector_state == DAQ_VALVE_UNK) ? "UNK" : "ILL",
             fill_tank_pressure, mass);
    lcd.print(line);
}

static void display_disconnect_line(valve_state_t injector_state,
                                    uint16_t fill_line_pressure, unsigned char linac_extend,
                                    unsigned char linac_retract)
{
    lcd.setCursor(0, 2);
    if (fill_line_pressure > 999)
        fill_line_pressure = 999;
    char line[21];
    snprintf(line, 21, "IV:%s PL:%03u RD:%s",
             (injector_state == DAQ_VALVE_OPEN) ? "OPN" :
             (injector_state == DAQ_VALVE_CLOSED) ? "CLS" :
             (injector_state == DAQ_VALVE_UNK) ? "UNK" : "ILL",
             fill_line_pressure,
             (linac_extend && !linac_retract) ? "DIS" :
             (!linac_extend && linac_retract) ? "CON" : "UNK");
    lcd.print(line);
}

static void display_ground_batt_line(uint16_t tower_act, uint16_t tower_main)
{
    lcd.setCursor(0, 3);
    char line[21];
    snprintf(line, 21, "BAT TA:%05uTM:%05u", tower_act, tower_main);
    lcd.print(line);
}

static void display_rocket_batt_line(uint16_t flight_bus_batt,
                                     uint16_t flight_vent_batt)
{
    lcd.setCursor(0, 3);
    char line[21];
    snprintf(line, 21, "BAT FB:%05uFV:%05u", flight_bus_batt, flight_vent_batt);
    lcd.print(line);
}

static void marquee_current_error()
{
    //exit conditions
    if (millis() - time_last_error_displayed > 5000) {
        currently_marqueeing_error = false;
        num_errors_queued--;
        marquee_buffer_index++;
        if (marquee_buffer_index >= 10)
            marquee_buffer_index = 0;
    }

    char line[21];
    snprintf(line, 20, "%s", buffer_to_marquee[marquee_buffer_index]);
    lcd.setCursor(0, 3);
    lcd.print(line);
}

static void marquee_next_error()
{
    time_last_error_displayed = millis();
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    currently_marqueeing_error = true;
}
