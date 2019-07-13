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
const int pulseSensorPin = 0;        // PulseSensor Signal (S) wire connected to ANALOG PIN 0 (A0)
int val;                            // Holds the incoming raw data. Signal value can range from 0-1024
int threshold = 135;                 // If sensor value exceeds this value, we detect a beat.


// The SetUp Function:
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);        // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
}

// The Main Loop Function
void loop() {

  val = analogRead(pulseSensorPin);  // Read the PulseSensor's value.
  // Assign this value to the "Signal" variable.

  Serial.println(val);                    // Send the Signal value to Serial Plotter.

  if (val > threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(BUILTIN_LED, HIGH);
  } else {
    digitalWrite(BUILTIN_LED, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
  }

  delay(10);
}
