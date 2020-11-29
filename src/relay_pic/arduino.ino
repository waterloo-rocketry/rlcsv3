// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);    // sets the digital pin 13 as output
  Wire.begin(); // join i2c bus (address optional for master)
  digitalWrite(LED_BUILTIN, LOW); // sets the digital pin 13 off
  Serial.begin(115200);  // start serial for output
  Serial.println("hi");
}

uint8_t x = 1;
uint8_t count = 0;

void loop()
{
  count += 1;
  if (count >= 50) {
    count = 0;
    if(x == 1) {
      x = 2;
      digitalWrite(LED_BUILTIN, HIGH); // sets the digital pin 13 on
    } else {
      x = 1;
      digitalWrite(LED_BUILTIN, LOW); // sets the digital pin 13 off
    }
    Wire.beginTransmission(3); // transmit to device #2
    Wire.write(x);             // sends one bytes
    Wire.endTransmission();    // stop transmitting
  }
  delay(50);
  
  Wire.requestFrom(3, 5);
  Serial.print("lims: ");
  uint8_t lims = Wire.read();
  Serial.println(lims);
  for (int i = 0; i < 2; i++) {
    uint8_t adcl = Wire.read();    // receive a byte
    uint8_t adch = Wire.read();    // receive a byte
    uint16_t current = (((uint16_t)adch << 8) | adcl) * 2;
    Serial.println(current);         // print the byte
  }
  delay(50);
}
