/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */
import processing.serial.*;
Serial myPort;      // Create object from Serial class
import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;
String remoteIP = "127.0.0.1";  // Set this to IP adress of computer/device you want to send OSC to.

int val; // Value received will be assigned to this

void setup() {
  size(400, 400);
  frameRate(25);

  // List all the available serial ports:
  printArray(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // In Windows, this usually opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[2]; // Change the number to a 1 or 2 etc. to match with the port the Arduino is connected to
  myPort = new Serial(this, portName, 115200);


  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);

  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. 
   */
  myRemoteLocation = new NetAddress(remoteIP, 9999);
}


void draw() {
  background(0);  
  // Everything happens in serialEvent()
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
}

void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n'); // Read data until end of line
  float valF = float(data);          
  val = int(valF); 
  println(val);
  OscMessage myMessage = new OscMessage("/test");
  myMessage.add(val); /* add an int to the osc message */
  /* send the message */
  oscP5.send(myMessage, myRemoteLocation);
}
