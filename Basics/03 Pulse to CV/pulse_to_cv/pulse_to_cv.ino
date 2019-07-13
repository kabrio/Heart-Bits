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
const int pulseSensorPurplePin = 0;     // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0

int sensorVal;                          // Holds the incoming raw data. Signal value can range from 0-1024
int threshold = 510;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");
  pinMode(BUILTIN_LED, OUTPUT);         // Setting pin of built in LED as output to be able to turn it on or off.

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x62);
}

void loop(void) {
  // Run through the full 12-bit scale for a triangle wave
  //  uint32_t counter;
  //    for (counter = 0; counter < 4095; counter++)
  //    {
  //      dac.setVoltage(counter, false);
  //    }
  //    for (counter = 4095; counter > 0; counter--)
  //    {
  //      dac.setVoltage(counter, false);
  //    }


  sensorVal = analogRead(pulseSensorPurplePin);  // Read the PulseSensor's value.
  // Map the values that we get from the pulse sensor to suitable values for the DAC
  int controlV = map(sensorVal, 480, 510, 2000, 4095);

  dac.setVoltage(controlV, false);      // Tell the DAC to output voltage based on controlVs value

  Serial.println(sensorVal);            // Send the signal value to Serial Plotter.


  if (sensorVal > threshold) {          // If the signal is above threshold, then turn on LED.
    digitalWrite(BUILTIN_LED, HIGH);
  } else {
    digitalWrite(BUILTIN_LED, LOW);     //  Else, the signal must be below threshold, so turn off this LED.
  }

}
