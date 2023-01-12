#include "lcd.hpp"
#include "common/mock_arduino.hpp"
#include "common/shared_types.hpp"
#include "config.hpp"
#include "pinout.hpp"
#include <stdio.h>

LiquidCrystal lcd{pinout::LCD_RS, pinout::LCD_EN, pinout::LCD_D4,
          pinout::LCD_D5, pinout::LCD_D6, pinout::LCD_D7};

static const char *valve_to_str(uint16_t pos) {
  switch (pos) {
  case ActuatorPosition::ActuatorPosition::error:
    return "ERR";
    break;
  case ActuatorPosition::ActuatorPosition::closed:
    return "CLS";
    break;
  case ActuatorPosition::ActuatorPosition::open:
    return "OPN";
    break;
  default:
    return "UNK";
  }
}

void LCDInit() {
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(2, 2);
  lcd.print("Waiting for data");
}

static uint8_t get_batt_dv() {
  return (analogRead(pinout::BATT_VOLTAGE) + config::BATT_SCALE_PRE_OFFSET)
       * config::BATT_SCALE_NUM / config::BATT_SCALE_DEN;
}

static void num_prettyprint(char *buf, unsigned int num) {
  snprintf(buf, 4, "%03d", num);
}

void LCDUpdate(SensorMessage msg) {
  char buf[4];

  lcd.setCursor(0, 0);
  lcd.print("V1:");
  lcd.print(valve_to_str(msg.valve_1_state));

  lcd.print(" V2:");
  lcd.print(valve_to_str(msg.valve_2_state));

  lcd.print(" LN:");
  lcd.print("DNE");

  lcd.setCursor(0, 1);
  lcd.print("IP:");
  num_prettyprint(buf, msg.ignition_primary_ma / 10);
  lcd.print(buf);

  lcd.print(" IS:");
  num_prettyprint(buf, msg.ignition_secondary_ma / 10);
  lcd.print(buf);

  lcd.print(" EC:");
  num_prettyprint(buf, msg.error_code);
  lcd.print(buf);

  lcd.setCursor(0, 2);
  lcd.print("TS:");
  // TODO: use new boolean values in the container
  //lcd.print((msg.towerside_state & 2) ? '1' : '0');
  //lcd.print((msg.towerside_state & 1) ? '1' : '0');
  //lcd.print((msg.towerside_state & 0) ? '1' : '0');

  lcd.print(" TM:");
  num_prettyprint(buf, msg.towerside_main_batt_mv / 100);
  lcd.print(buf);

  lcd.print(" TA:");
  num_prettyprint(buf, msg.towerside_actuator_batt_mv / 100);
  lcd.print(buf);

  lcd.setCursor(0, 3);
  lcd.print("CB:");
  num_prettyprint(buf, get_batt_dv());
  lcd.print(buf);
}
