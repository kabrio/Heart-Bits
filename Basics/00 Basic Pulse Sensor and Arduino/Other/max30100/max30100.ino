/*
  Arduino-MAX30100 oximetry / heart rate integrated sensor library
  Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     50
// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;
uint32_t tsLastReport = 0;
uint32_t tsLastBeat = 0;
int led = 13;
int sol = 12;
int intv = 0;
bool beating = false;
bool measuring = false;
unsigned long lastbeat = 0;
float avg = 0;
// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
  digitalWrite( led, HIGH );
  digitalWrite( sol, HIGH );
  float r = pox.getHeartRate();
  if ( millis() - tsLastBeat < 1500 ) {
    //    Serial.println( "Finger detected" );
    avg = runningAverage( r );
    intv = ( 60 / avg ) * 1000; // bpm to interval in ms
    //    digitalWrite( sol, LOW );
    beating = false;
  } else {
    beating = true;
  }
  //  Serial.print( "rate: " );
  //  Serial.println( r );
  Serial.print( " avg: " );
  Serial.print( avg );
  Serial.print( " intv: " );
  Serial.println( intv );
  tsLastBeat = millis();
}
void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  // The default current for the IR LED is 50mA and it could be changed
  //   by uncommenting the following line. Check MAX30100_Registers.h for all the
  //   available options.
  // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
  pinMode( led, OUTPUT );
  pinMode( sol, OUTPUT );
}
void loop()
{
  // Make sure to call update as fast as possible
  pox.update();
  if (millis() - tsLastBeat > 300) { // turn the led off after 300ms
    digitalWrite( led, LOW );
  }
  if ( beating ) {
    int m = millis();
    //    Serial.print( "mil: " );
    //    Serial.print( m );
    //    Serial.print( " last: " );
    //    Serial.print( lastbeat );
    //    Serial.print( " " );
    //    Serial.print( m - lastbeat );
    //    Serial.print( " invt: " );
    //    Serial.println( intv );
    if ( millis() - lastbeat > intv ) { // turn the solenoid on
      digitalWrite( sol, HIGH );
    }
    if ( millis() - lastbeat > intv + 100 ) { // turn the solenoid off and reset counter
      digitalWrite( sol, LOW );
      lastbeat = millis();
    }
  }
  if ( millis() - tsLastBeat > 1500 ) {
    beating = true;
  }
}
#define LM_SIZE 10
static int LM[LM_SIZE];      // LastMeasurements
static byte index = 0;
static long sum = 0;
static byte count = 0;
long runningAverage(int M) {
  // keep sum updated to improve speed.
  sum -= LM[index];
  LM[index] = M;
  sum += LM[index];
  index++;
  index = index % LM_SIZE;
  if (count < LM_SIZE) count++;
  return sum / count;
}
void clearAverage() {
  for ( int i = 0; i < LM_SIZE; i++ ) {
    LM[ i ] = 0;
  }
}
