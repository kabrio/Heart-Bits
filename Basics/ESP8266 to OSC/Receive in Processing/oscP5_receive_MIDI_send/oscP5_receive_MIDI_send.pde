import themidibus.*;

import oscP5.*;
import netP5.*;

//OSC
OscP5 oscP5;
NetAddress myRemoteLocation;
int oscVal = 0, prevOscVal = 0;

//MIDI
MidiBus myBus; 
int channel = 0; //MIDI channel to use  (0 - 15)
int pitch = 64;  //default MIDI pitch = note  (0 - 127)
int velocity = 127; //default MIDI velocity = loudness (0 - 127)


void setup() {
  size(400, 400);
  frameRate(25);
  
//MIDI
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
  //                 Parent  In  Out
  //                   |     |   |
  myBus = new MidiBus(this, -1,  1); // Create a new MidiBus with no input device and the default Java Sound Synthesizer as the output device.
  
      
  //OSC
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 9999);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1", 12000);
}


void draw() {
  background(0);
  //println(oscVal);
}

void mousePressed() {
  /* in the following different ways of creating osc messages are shown by example */
  OscMessage myMessage = new OscMessage("/test");

  myMessage.add(123); /* add an int to the osc message */

  /* send the message */
  oscP5.send(myMessage, myRemoteLocation);
}


/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  
  // only update oscVal if it has changed
  if (prevOscVal != theOscMessage.get(0).intValue()) {
    oscVal = theOscMessage.get(0).intValue();
    prevOscVal = oscVal;
    println(" value: "+oscVal);
  }
  

    
  //let's send our osc value to a midi synth
  myBus.sendNoteOn(channel, oscVal, velocity); // Send a Midi noteOn
  delay(200);
  myBus.sendNoteOff(channel, oscVal, velocity); // Send a Midi nodeOff
}


// This is an upgrade to the standard delay function and prevents the whole sketch from stopping while waiting for delay()  
void delay(int time) {
  int current = millis();
  while (millis () < current+time) Thread.yield();
}
