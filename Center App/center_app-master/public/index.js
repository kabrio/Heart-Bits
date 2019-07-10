var socket = io();
socket.on('connect', function(data){
  console.log('socket connected')
  socket.emit('ready')
});

socket.on('signal', function(pulseObj){
  console.log('got the signal', pulseObj);
  // singal = {
  //  bpm: int,
  //  pulse: int
  //}

  pulse = pulseObj;
  // Inserting data in dom with data from #stream
  // document.getElementById('stream').innerHTML = signal;
});

var pulse = {};

// socket.on('IBI', function(ibi){
//   console.log('got IBI', ibi);
//   interval = ibi;
//   console.log(interval);
//
// });
//
// var interval = []
