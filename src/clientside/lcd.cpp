#include <stdio.h>

#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"
#include "config.hpp"
#include "lcd.hpp"
#include "pinout.hpp"

namespace {

LiquidCrystal liquid_crystal{pinout::LCD_RS, pinout::LCD_EN, pinout::LCD_D4,
                             pinout::LCD_D5, pinout::LCD_D6, pinout::LCD_D7};

void print_valve_position(uint16_t pos) {
  const char *s;
  switch (pos) {
  case ActuatorPosition::ActuatorPosition::error:
    s = "ERR";
    break;
  case ActuatorPosition::ActuatorPosition::closed:
    s = "CLS";
    break;
  case ActuatorPosition::ActuatorPosition::open:
    s = "OPN";
    break;
  default:
    s = "UNK";
  }
  liquid_crystal.print(s);
};

uint8_t get_batt_dv() {
  return (analogRead(pinout::BATT_VOLTAGE) + config::BATT_SCALE_PRE_OFFSET) *
         config::BATT_SCALE_NUM / config::BATT_SCALE_DEN;
}

void print_decimal_value(unsigned int num) {
  char buf[4];
  snprintf(buf, 4, "%03d", num);
  liquid_crystal.print(buf);
}

} // namespace

void lcd::lcd_init() {
  liquid_crystal.begin(20, 4);
  liquid_crystal.clear();
  liquid_crystal.setCursor(2, 2);
  liquid_crystal.print("Waiting for data");
}

void lcd::lcd_update(SensorMessage msg) {
  liquid_crystal.setCursor(0, 0);
  liquid_crystal.print("V1:");
  print_valve_position(msg.valve_1_state);

  liquid_crystal.print(" V2:");
  print_valve_position(msg.valve_2_state);

  liquid_crystal.print(" ARM:");
  liquid_crystal.print(msg.towerside_armed ? "Y" : "N");

  liquid_crystal.setCursor(0, 1);
  liquid_crystal.print("IP:");
  print_decimal_value(msg.ignition_primary_ma / 10);

  liquid_crystal.print(" IS:");
  print_decimal_value(msg.ignition_secondary_ma / 10);

  liquid_crystal.print(" EC:");
  print_decimal_value(msg.error_code);

  liquid_crystal.setCursor(0, 2);
  liquid_crystal.print("TCOM:");
  liquid_crystal.print(msg.has_contact ? "Y" : "N");

  liquid_crystal.print(" TM:");
  print_decimal_value(msg.towerside_main_batt_mv / 100);

  liquid_crystal.print(" TA:");
  print_decimal_value(msg.towerside_actuator_batt_mv / 100);

  liquid_crystal.setCursor(0, 3);
  liquid_crystal.print("CB:");
  print_decimal_value(get_batt_dv());
}
