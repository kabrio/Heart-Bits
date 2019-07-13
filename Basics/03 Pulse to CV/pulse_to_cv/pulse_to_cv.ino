/**************************************************************************/
/*! 
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a triangle wave with the MCP4725 DAC.   

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935
 
    Adafruit invests time and resources providing this open source code, 
    please support Adafruit and open-source hardware by purchasing 
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;


//  Pulsesensor variables
int pulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int led13   = 13;   //  The on-board Arduion LED


int sensorVal;                // holds the incoming raw data. Signal value can range from 0-1024
int threshold = 510;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x62);
    
  Serial.println("Generating a triangle wave");
}

void loop(void) {
    uint32_t counter;
    // Run through the full 12-bit scale for a triangle wave
//    for (counter = 0; counter < 4095; counter++)
//    {
//      dac.setVoltage(counter, false);
//    }
//    for (counter = 4095; counter > 0; counter--)
//    {
//      dac.setVoltage(counter, false);
//    }

    
  sensorVal = analogRead(pulseSensorPurplePin);  // Read the PulseSensor's value.

int controlV = map(sensorVal, 480, 510, 2000, 4095);

dac.setVoltage(controlV, false);

   Serial.println(sensorVal);                    // Send the Signal value to Serial Plotter.


   if(sensorVal > threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(led13,HIGH);
   } else {
     digitalWrite(led13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }

}
