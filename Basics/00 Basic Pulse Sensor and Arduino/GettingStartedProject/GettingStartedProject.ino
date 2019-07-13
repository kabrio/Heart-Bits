/*  PulseSensor Starter Project and Signal Tester
    The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.

    Here is a link to the tutorial
    https://pulsesensor.com/pages/code-and-guide

    WATCH ME (Tutorial Video):
    https://www.youtube.com/watch?v=RbB8NSRa5X4


  -------------------------------------------------------------
  1) This shows a live human Heartbeat Pulse.
  2) Live visualization in Arduino's Cool "Serial Plotter".
  3) Blink an LED on each Heartbeat.
  4) This is the direct Pulse Sensor's Signal.
  5) A great first-step in troubleshooting your circuit and connections.
  6) "Human-readable" code that is newbie friendly."

*/


//  Variables
const int pulseSensorPin = 0;        // Pulse Sensor signal (S) wire connected to ANALOG PIN 0 (A0)
int sensorVal;                       // Holds the incoming raw data. Signal value can range from 0-1024
int threshold = 135;                 // If sensor value exceeds this value, we detect a beat.


// The SetUp Function:
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Setting pin of built in LED as output to be able to turn it on or off.
  Serial.begin(115200);            // Set's up Serial Communication at certain speed.
}

// The Main Loop Function
void loop() {

  sensorVal = analogRead(pulseSensorPin);  // Read the PulseSensor's value.
  // Assign this value to the "Signal" variable.

  Serial.println(sensorVal);                    // Send the signal value to Serial Plotter.

  if (sensorVal > threshold) {                      // If the signal is above threshold, then turn on LED.
    digitalWrite(BUILTIN_LED, HIGH);
  } else {
    digitalWrite(BUILTIN_LED, LOW);               //  Else, the signal must be below threshold, so turn off this LED.
  }

  delay(10);
}
