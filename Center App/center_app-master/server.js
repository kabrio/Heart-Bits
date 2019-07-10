// Express
// =======
const express = require('express');
const app = express();
const port = process.env.PORT || 8081;
const server = app.listen(port, function () {
               console.log('Listening on port: ' + port);
             });

app.use(express.static('public'));

// This is how I will write routes:
// app.get('/', function (req, res) {
// })


//socket.io
// ========
var socket = require('socket.io');

// var io chains together server and socket.io modules:
var io = socket(server);

// This is how to set up a listener for socket.io:
io.sockets.on('connection', function(socket){
  console.log('new connection from:' + socket.id);
  socket.on('ready', function(){
    console.log('got ready signal from Front-End')
    connectSerial();
  });
});

// Pulse Functions
// ===============
function connectSerial() {
  var $ = require('jQuery');
  var SerialPort = require('serialport');
  var createInterface = require('readline').createInterface;
  var usbPort = '/dev/cu.usbmodemFA131';
  var port = new SerialPort(usbPort);
  var lineReader = createInterface({
    input: port
  });
  // console.log(lineReader);



//

  // var PulseSensor = require('pulsesensor');
  // var pulse = PulseSensor.use(usbPort);
  // pulse.on('ready', function (){
  //   pulseSensor.on('beat', function (time) {
  //     console.log(pulse.BPM);
  //   });
  // });
//
  var ibiArray = []
  var variance;
  var varianceArray = []

  lineReader.on('line', function (line) {
    // split into two numbers by ,
    var l = line.split(',')
    // ["0", "120"]
    var obj = {}
    obj.bpm = parseInt(l[0])
    obj.pulse = parseInt(l[1])
    obj.ibi = parseInt(l[2])
    obj.previousVariance = varianceArray[0];
    obj.variance = variance;

    // HRV
    // ibiArray = [900, 992, 1000]
    if (obj.ibi !== ibiArray[ibiArray.length - 1] && (typeof obj.ibi === 'number') && isNaN(obj.ibi) !== true) {
      ibiArray.push(obj.ibi)
      // console.log(ibiArray)
      if (ibiArray.length > 10) {
        ibiArray.shift()
        // console.log(ibiArray)
        variance = calculateVariance(ibiArray);
        obj.variance = variance;
        varianceArray.push(obj.variance);
          if (varianceArray.length > 2) {
            varianceArray.shift()
          }
      }
    }

    function calculateVariance(nums) {
      var diff = 0;
      // process var
      var total = 0;
      var avg = 0;
      var allDiffs= [];

      for(var i = 0; i < nums.length; i++) {
        total += nums[i];
      }

      avg = total / nums.length;

      for(var i = 0; i < nums.length; i++) {
        var diff = Math.abs(nums[i] - avg);
        allDiffs.push(diff);
      }

      var diffTotal = 0;
      for(var i = 0; i < allDiffs.length; i++) {
        diffTotal += allDiffs[i];
      }

      var variance = diffTotal / allDiffs.length;
      return variance;
    }

    // obj = {
    //   bpm: "0"
    //   pulse: "120"
    // }
    // convert these into integers
    console.log(obj);
    io.sockets.emit('signal', obj);


    // console.log('req emit here...')

    //  printing the numbers to the html from the arduino (needs io or it is out of scope)
    // emit one number
    // ===============
    // io.sockets.emit('signal', line);

    // emit array of numbers
    // =====================
  //   data.push(line);
  //   // console.log(data);
  //   // if (data.length >= 10) {
  //   if (data.length >= 2) {
  //     var regularity = evaluateRegularity(data);
  //     io.sockets.emit('signal', regularity);
  //     data = [];
  //   }
  });
  //
  // var data = [];
  // function evaluateRegularity(data) {
  //   // evaluate data and send back number that represents regularity
  //   return data;

  port.write('ROBOT PLEASE RESPOND\n');
}
