#include "lcd.hpp"
#include "common/mock_arduino.hpp"

#include <stdio.h>

#include "common/shared_types.hpp"
#include "config.hpp"
#include "hardware.hpp"
#include "pinout.hpp"

namespace lcd {

LiquidCrystal liquid_crystal{pinout::LCD_RS, pinout::LCD_EN, pinout::LCD_D4,
                             pinout::LCD_D5, pinout::LCD_D6, pinout::LCD_D7};

void print_valve_position(uint16_t pos) {
  switch (pos) {
  case ActuatorPosition::ActuatorPosition::error:
    liquid_crystal.print("ERR");
    break;
  case ActuatorPosition::ActuatorPosition::closed:
    liquid_crystal.print("CLS");
    break;
  case ActuatorPosition::ActuatorPosition::open:
    liquid_crystal.print("OPN");
    break;
  case ActuatorPosition::ActuatorPosition::unknown:
    liquid_crystal.print("UNK");
    break;
  default:
    liquid_crystal.print("???");
    break;
  }
  liquid_crystal.print(" ");
};

void print_towerside_state(sequence::State state) {
  switch (state) {
    case sequence::State::MANUAL:
      liquid_crystal.print("MAN");
      break;
    case sequence::State::AUTOMATIC:
      liquid_crystal.print("AUT");
      break;
    case sequence::State::SEQUENCE1:
      liquid_crystal.print("AS1");
      break;
    case sequence::State::SEQUENCE2:
      liquid_crystal.print("AS2");
      break;
    default:
      liquid_crystal.print("???");
      break;
  }
  liquid_crystal.print(" ");
}

void print_decimal_value(unsigned int num) {
  char buf[4];
  snprintf(buf, 4, "%03u", num);
  liquid_crystal.print(buf);
}

void setup() {
  liquid_crystal.begin(20, 4);
  liquid_crystal.clear();
  liquid_crystal.setCursor(2, 1);
  liquid_crystal.print("Waiting for data");
  liquid_crystal.setCursor(14, 3);
  liquid_crystal.print("CB:");
  print_decimal_value(hardware::get_batt_dv());
}

/* Layout:
   ----------------------
   |O1:OPN O2:CLS O3:UNK|
   |IP:412 IS:456       | Those current are in hundredth(increment 0.01)
   |E:000 CON:Y ARM:Y tH|
   |TM:123 TA:118 CB:126| Those voltage are in tenth(increment 0.1)
   ----------------------
*/

void update(SensorMessage msg) {
  //liquid_crystal.clear();
  liquid_crystal.setCursor(0, 0);
  liquid_crystal.print("STE:");
  print_towerside_state(msg.state);
  liquid_crystal.print("S-IDX:");
  char str[8];
  itoa( msg.sequence_idx, str, 10 );
  liquid_crystal.print(str);

  liquid_crystal.setCursor(0, 1);
  liquid_crystal.print("KAVIN WAS HERE ;D ");

  /*
  liquid_crystal.print("NV102:");
  print_valve_position(msg.NV102_state);
  liquid_crystal.print("NV103:");
  print_valve_position(msg.NV103_state);
  liquid_crystal.print("NV104:");
  print_valve_position(msg.NV103_state);
  liquid_crystal.print("NV105:");
  print_valve_position(msg.NV103_state);
  liquid_crystal.print("OV102:");
  print_valve_position(msg.OV102_state);
  liquid_crystal.print("FV102:");
  print_valve_position(msg.FV102_state);
  liquid_crystal.print("OV101:");
  print_valve_position(msg.OV101v_state);
  liquid_crystal.print("FV101:");
  print_valve_position(msg.FV101v_state);
  */

  liquid_crystal.setCursor(0, 2);
  liquid_crystal.print("E:");
  print_decimal_value(msg.error_code);

  liquid_crystal.print(" CON:");
  liquid_crystal.print(msg.has_contact ? "Y" : "N");

  liquid_crystal.print(" ARM:");
  liquid_crystal.print(msg.towerside_armed ? "Y" : "N");

  /*
  if(msg.heater_kelvin_high_mv_1 >= 16000) {
    liquid_crystal.print(" T");
  }else{
    liquid_crystal.print(" t");
  }

  if(msg.heater_kelvin_high_mv_2 >= 16000) {
    liquid_crystal.print("H");
  }else{
    liquid_crystal.print("h");
  }
  */

  liquid_crystal.setCursor(0, 3);
  liquid_crystal.print("TM:");
  print_decimal_value(msg.towerside_main_batt_mv / 100);

  liquid_crystal.print(" TA:");
  print_decimal_value(msg.towerside_actuator_batt_mv / 100);

  liquid_crystal.print(" CB:");
  print_decimal_value(hardware::get_batt_dv());



    /* TODO: fix this

  liquid_crystal.setCursor(0, 1);

  liquid_crystal.print("IP:");
  print_decimal_value(msg.ignition_primary_ma / 10);
 
  liquid_crystal.print(" IS:");
  print_decimal_value(msg.ignition_secondary_ma / 10);

  liquid_crystal.print("       ");

  
  */
}

} // namespace lcd
