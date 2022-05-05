#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "common/mock_arduino.hpp"
#include "common/communication/receiver.hpp"
#include "common/shared_types.hpp"
#include "config.hpp"
#include "pinout.hpp"

namespace DataHandler {

class LCDDisplay: public Communication::MessageHandler<SensorData> {
  LiquidCrystal lcd {Pinout::LCD_RS, Pinout::LCD_EN, Pinout::LCD_D4, Pinout::LCD_D5, Pinout::LCD_D6, Pinout::LCD_D7};
  uint8_t n;
  SensorID::SensorID *sensors;
  public:
    template <typename... Sensors>
    LCDDisplay(Sensors... sensors):
        n{sizeof...(sensors)}, sensors{new SensorID::SensorID[n]{sensors...}} {
      lcd.begin(20, 4);
      lcd.clear();
    }
    void handle(const SensorData &msg) override {
      uint8_t row = 0;
      char line[21];
      char *cursor = line;
      for (uint8_t i = 0; i < n; i++) {
        SensorID::SensorID sensor = sensors[i];
        Channel::Channel *channel = Config::get_channel(sensor);
        strncpy(cursor, channel->get_id(), 2); cursor += 2;
        cursor[0] = ':'; cursor += 1;
        cursor += channel->format(msg.get_sensor(sensor), cursor); // return value is length written
        
        if (cursor - line > 20 - 6 || i == n - 1) { // no space left on this line, or this is the last value
          cursor[0] = '\0';
          lcd.setCursor(0, row);
          lcd.print(line);
          row++;
          memset(line, '\0', 21);
          cursor = line;
        } else {
          cursor[0] = ' '; cursor += 1;
        }
      }

    }
};

}

#endif
