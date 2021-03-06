//Import the library
import processing.serial.*;
import themidibus.*; 

// Variables

MidiBus myBus;           // The MidiBus - for sending/receiving data to/from MIDI device
Serial myPort;           // Create object from Serial class
int channel = 0;         // The MIDI device you are using 

// For controlVCOWave and controlEGType the values should be changed to fit the control numbers of the device you are using
int controlVCOWave = 51; // The control number of VCO Wave control for Korg Monologue
int controlEGType = 61;  // The control number of EG Type control for Korg Monologue

int valueEGType = 127;   // The initial value of VCO Wave control
int valueVCOWave = 127;  // The initial value of EG Type control

int noteValue = 64;      // The initial value of the note that will play
int velocity = 36;       // The initial value of the velocity that will play

String val;              // Data received from the serial port as String
float valF;              // float value of val
int valI;                // integer value of val
                         // Arduino int is shorter than Processing int so direct conversion 
                         // from String to int doesn't give the correct value

int treshold = 510;      // Pulse value treshold 
                         // This may be different for everyone and changes during time

int count = 0;           // Counter used to change controls after certain number of heartbeats

//The SetUp Function
void setup() {
  String portName = Serial.list()[1];           // change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);  // port number must match the one setup in Arduino
  size(400, 400);                               // size of the sketch (not really important for this example)
  background(0);                                // background color of the sketch (not really important for this example)

  MidiBus.list();                               // List all available Midi devices on STDOUT. This will show each device's index and name.

  // Either you can
  //                   Parent In Out
  //                     |    |  |
  //myBus = new MidiBus(this, 0, 1); // Create a new MidiBus using the device index to select the Midi input and output devices respectively.

  // or you can ...
  //                   Parent         In                   Out
  //                     |            |                     |
  //myBus = new MidiBus(this, "IncomingDeviceName", "OutgoingDeviceName"); // Create a new MidiBus using the device names to select the Midi input and output devices respectively.

  //                 Parent In Out
  //                   |    |  |
  myBus = new MidiBus(this, 1, 2); // Create a new MidiBus
  
  // Initial setting of VCO Wave control and EG Type control
  myBus.sendControllerChange(channel, controlVCOWave, valueVCOWave);
  myBus.sendControllerChange(channel, controlEGType, valueEGType);
}

// The main function that executes in a loop
void draw() {
  count++;                                        // tracking the number of heartbeats
  if ( myPort.available() > 0) {                  // If data is available,
    val = myPort.readStringUntil('\n');           // read the data from the port until new line
    valF = float(val);                            // and convert it to float
    valI = int(valF);                             // and convert it to int
  }
  
  noteValue = (int) map(valI, 490, 520, 36, 64);  // Mapping the heartbeat value (valI) to note value
                                                  // 490, 520 - range of the heartbeat value, change it to fit your needs
                                                  // 36, 56 - range of the note value, change it to fit your needs
  //println("noteValue " + noteValue);              // Printing note values in the console

  myBus.sendNoteOn(channel, noteValue, velocity); // Send a Midi noteOn
  delay(200);                                     // Duration of the note - can be changed
  myBus.sendNoteOff(channel, noteValue, velocity);// Send a Midi nodeOff

  if (count > 30 && count < 50) {    
    println("hey");
    valueEGType = 64;                              // Changing the EG Type after 20 heartbeats

    myBus.sendControllerChange(channel, controlEGType, valueEGType); // Send a controllerChange for EG Type
    //delay(2000);                                // uncomment if you want to add delay between the changes
  }
  
  if (count > 50) {   
        println("heyhey");

    valueVCOWave = 0;                            // Changing the EG Type after 30 heartbeats

    myBus.sendControllerChange(channel, controlVCOWave, valueVCOWave); // Send a controllerChange for VCOWave
    //delay(2000);                                // uncomment if you want to add delay between the changes
  }
}

void noteOn(int channel, int noteValue, int velocity) {
  // Receive a noteOn
  println();
  println("Note On:");
  println("--------");
  println("Channel:"+channel);
  println("noteValue:"+noteValue);
  println("Velocity:"+velocity);
}

void noteOff(int channel, int noteValue, int velocity) {
  // Receive a noteOff
  println();
  println("Note Off:");
  println("--------");
  println("Channel:"+channel);
  println("noteValue:"+noteValue);
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
