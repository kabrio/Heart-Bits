import processing.serial.*;

import themidibus.*; //Import the library


MidiBus myBus; // The MidiBus
int controlVCOWave = 51;
int controlEGType = 61;
int valueEGType = 127;
int valueVCOWave = 127;
int channel = 0;
int pitch = 64;
int velocity = 127;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
float valF;

int treshold = 510; //this may be different for everyone and changes during time

int count = 0;

void setup() {
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
  size(400, 400);
  background(0);

  MidiBus.list(); // List all available Midi devices on STDOUT. This will show each device's index and name.

  // Either you can
  //                   Parent In Out
  //                     |    |  |
  //myBus = new MidiBus(this, 0, 1); // Create a new MidiBus using the device index to select the Midi input and output devices respectively.

  // or you can ...
  //                   Parent         In                   Out
  //                     |            |                     |
  //myBus = new MidiBus(this, "IncomingDeviceName", "OutgoingDeviceName"); // Create a new MidiBus using the device names to select the Midi input and output devices respectively.

  // or for testing you could ...
  //                 Parent  In        Out
  //                   |     |          |
  myBus = new MidiBus(this, 1, 2); // Create a new MidiBus with no input device and the default Java Sound Synthesizer as the output device.
  
  myBus.sendControllerChange(channel, controlEGType, valueEGType);
  myBus.sendControllerChange(channel, controlVCOWave, valueVCOWave);
}

void draw() {
  count++;
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.readStringUntil('\n');
    valF = float(val);
    println((int)valF);

  } 
  int valI = int(valF);
  pitch = (int) map(valI, 490, 520, 36, 56);
  //pitch = (int) (noise (random (valF%96))*96);
  println("pitch " + pitch);
  velocity = 36;
  println("vel " + velocity);

  myBus.sendNoteOn(channel, pitch, velocity); // Send a Midi noteOn
  delay(1000);
  myBus.sendNoteOff(channel, pitch, velocity); // Send a Midi nodeOff

  if (count > 20) {
    println("change");
    
    valueEGType = 0;

    myBus.sendControllerChange(channel, controlEGType, valueEGType); // Send a controllerChange
    //delay(2000);
  }
  
  if (count > 30) {
    println("changeeee");
     
    valueVCOWave = 0;

    myBus.sendControllerChange(channel, controlVCOWave, valueVCOWave); // Send a controllerChange
    //delay(2000);
  }
}

void noteOn(int channel, int pitch, int velocity) {
  // Receive a noteOn
  println();
  println("Note On:");
  println("--------");
  println("Channel:"+channel);
  println("Pitch:"+pitch);
  println("Velocity:"+velocity);
}

void noteOff(int channel, int pitch, int velocity) {
  // Receive a noteOff
  println();
  println("Note Off:");
  println("--------");
  println("Channel:"+channel);
  println("Pitch:"+pitch);
  println("Velocity:"+velocity);
}

void controllerChange(int channel, int number, int value) {
  // Receive a controllerChange
  println();
  println("Controller Change:");
  println("--------");
  println("Channel:"+channel);
  println("Number:"+number);
  println("Value:"+value);
}

void delay(int time) {
  int current = millis();
  while (millis () < current+time) Thread.yield();
}
