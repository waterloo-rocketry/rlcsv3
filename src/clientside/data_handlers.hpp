#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/shared_types.hpp"
#include "config.hpp"
#include "daq.hpp"
#include "pinout.hpp"

namespace DataHandler {

// Handle data from towerside by displaying it on the LCD.
class LCDDisplay: public Communication::MessageHandler<SensorData> {
  // Use the arduino LiquidCrystal library
  LiquidCrystal lcd {Pinout::LCD_RS, Pinout::LCD_EN, Pinout::LCD_D4, Pinout::LCD_D5, Pinout::LCD_D6, Pinout::LCD_D7};
  // Keep an array of which sensors to display on the screen
  uint8_t n;
  SensorID::SensorID *sensors;
  public:
    // These template shenanigans let us take a variable number of arguments and dump them into the heap-allocated sensors array
    template <typename... Sensors>
    LCDDisplay(Sensors... sensors):
        // n stores the length of the array, sensors gets initialized with whatever arguments we got
        n{sizeof...(sensors)}, sensors{new SensorID::SensorID[n]{sensors...}} {
      lcd.begin(20, 4);
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("WAITING FOR DATA");
    }
    void handle(const SensorData &msg) override {
      // Build one row of the LCD at a time and print it out. Also prints the clientside battery
      // voltage at the end since it's a massive pain to fit in anywhere else. I'm sorry.
      // The format is a two character ID followed by a colon and a 3 character value. Eg: `IJ:OPN`
      uint8_t row = 0;
      char line[21]; // 20 character LCD plus null terminator
      char *cursor = line; // point to the next character to update in line
      for (uint8_t i = 0; i < n + 1; i++) { // n + 1 for the battery voltage
        if (i < n) { // a normal sensor
          SensorID::SensorID sensor = sensors[i];
          Channel::Channel *channel = Config::get_channel(sensor);
          strncpy(cursor, channel->get_id(), 2); cursor += 2; // two character ID
          cursor[0] = ':'; cursor += 1; // colon
          cursor += channel->format(msg.get_sensor(sensor), cursor); // return value is length written, should be 3
        } else {
          // Draw the clientside battery voltage.
          strncpy(cursor, "CB:", 3); cursor += 3;
          // here we don't avoid the null terminator since this is the end of the line anyways
          snprintf(cursor, 4, "%03u", DAQ::get_batt_dv()); cursor += 3;
        }

        if (cursor - line > 20 - 6 || i == n) { // no space left on this line, or this is the last value
          cursor[0] = '\0'; // end the line
          // print it
          lcd.setCursor(0, row);
          lcd.print(line);
          // clear line and reset for a new one
          row++;
          memset(line, '\0', 21);
          cursor = line;
        } else { // more data to come on this line
          cursor[0] = ' '; cursor += 1; // put a space between fields
        }
      }

    }
};

}

#endif
