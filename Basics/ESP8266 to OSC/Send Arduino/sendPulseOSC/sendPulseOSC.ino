/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266

  Example for sending messages from the ESP8266 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

  --------------------------------------------------------------------------------------------- */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "die basis";          // your network SSID (name)
char pass[] = "chesini93pornbike";  // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10, 0, 1, 108);       // remote IP of the computer to receive OSC. Note: this might change.
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

// Pulse Sensor
int pulseSensorPurplePin = 0;        // Pulse Sensor signal wire connected to ANALOG PIN 0
int val;                            // holds the incoming raw data. Signal value can range from 0-1024
int threshold = 135;                 // If val exceeds this value, we detect a beat.

void setup() {
  Serial.begin(9600);
  pinMode(BUILTIN_LED, OUTPUT);         // pin that will blink to your heartbeat!

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());

}

void loop() {
  int val = analogRead(pulseSensorPurplePin);     // Read the PulseSensor's value.
  Serial.println(val);                            // Send the Signal value to Serial Plotter.

  if (val > threshold) {                         // If the signal is above threshold, then turn-on LED.
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);             //  Else, the signal must be below threshold, so "turn-off" this LED.
  }


  OSCMessage msg("/esp/pulse");
  msg.add(val);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  delay(10);
}
