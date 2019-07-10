# Center is a biofeedback tool for meditation.
It is a Node.js program which runs on Pulse Sensor and Arduino. It creates a mesmerizing visualization of your heart rate which is meant not only to calm you, but to help you learn how to calm yourself more effectively. 

![app visualization](https://github.com/avalliere/socket-biofeedback/blob/master/calm-down-pulse-sensor%20copy.gif)

Keeping the waves of your heart rate steady will center them in the screen as a shallow undulation. An unsteady, anxious heart rate will send disjointed waves dashing across the screen. As you use the app, you will discover which meditation techniques are serving you well and which aren't as calming as you may have assumed.

This app was developed in one month as my Capstone project for [Ada Developers Academy](https://adadevelopersacademy.org).

## Setup/installation

### Third-party dependencies/Configuration

Frameworks, libraries and node packages required: 
Serialport, socket.io, p5.js, Express Server

## Parts list & Assembly

### Gather Parts & Software

This app was made with [Arduino Uno R3](https://www.adafruit.com/product/50) and [Pulse Sensor](https://pulsesensor.com/).

[Arduino IDE](https://www.arduino.cc/en/Main/Software) can be used to upload interrupt.ino to the Arduino board. Though not necessary, a breadboard and LED are fun to use to get started with the Pulse Sensor and familiarize yourself with Arduino basics. I used [this kit](https://www.adafruit.com/product/193) for this project.

### Assembly

Some quick setup of the Pulse Sensor is required to get started. Place an included clear vinyl protective sticker to the face of the sensor and a velcro sticker to the back of the sensor for use with the finger strap. The wires plug directly into the Arduino. Interrupt.ino (as well as the Pulse Sensor starter code) is expecting the black ground wire to be plugged into "ground", the red power wire plugs into "5V", and the purple wire goes to "A0". 

![GIF of Pulse Sensor assembly](https://github.com/avalliere/socket-biofeedback/blob/master/plug-pulse-sensor.gif)

A great starter video is available from PulseSensor.com and can be watched from the corresponding GitHub repo [here](https://github.com/WorldFamousElectronics/PulseSensorStarterProject).

## Other Capstone Details

[Product Plan](https://gist.github.com/avalliere/b7f1631b4bcf40171485920ebdfe9a03)

[Project Trello board](https://trello.com/b/gFBr9Doy/capstone)

