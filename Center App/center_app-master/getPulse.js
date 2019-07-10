var $ = require('jQuery');
var SerialPort = require('serialport');
var createInterface = require('readline').createInterface;
var usbPort = '/dev/cu.usbmodemFA131';

var port = new SerialPort(usbPort);
var lineReader = createInterface({
  input: port
});

lineReader.on('line', function (line) {
  console.log(line);
});

port.write('ROBOT PLEASE RESPOND\n');
