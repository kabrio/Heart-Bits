//
// function setup() {
//   var myCanvas = createCanvas(windowWidth, windowHeight);
//   myCanvas.parent('display');
//   background(200, 200, 200);
//
// }
//
// function draw() {
//   // pulse only experimental visualization
//   // // background(0, 50, pulse[2] / 3);
//   // background(0, 50, pulse[1]);
//   // // line(30, 20, 85, 75);
//   // // line(30, 20, pulse[0], pulse[1]);
//   // // line(100, pulse[0], 100, pulse[1]);
//   // // stroke(126);
//   // // ellipse(pulse[0] / 5, pulse[1] / 5, pulse[0] / 8, pulse[1] / 8);
//   // ellipse(pulse[0], pulse[1], pulse[0] / 2, pulse[1] / 2);
//
//   // pulse and BPM
//   // background(0, pulse.bpm, 250);
//
//   // ui gradient "purple bliss"
//   var high = color(54, 0, 51);
//   var midHigh = color(39, 45, 83);
//   var midLow = color(25, 90, 115);
//   var low = color(11, 135, 147);
//
//
//   if (pulse.bpm < 61) {
//     background(low)
//   } else if (pulse.bpm > 61 && pulse.bpm < 70) {
//     background(midLow)
//   } else if (pulse.bpm > 69 && pulse.bpm < 80) {
//     background(midHigh)
//   } else {
//     background(high)
//   };
//
//   fill(50, 0, pulse.bpm * 2, 50);
//   noStroke();
//   ellipse(80, 80, pulse.pulse / 8, pulse.pulse / 8);
//   ellipse(100, 25, pulse.pulse / 10, pulse.pulse / 10);
//   ellipse(30, 300, pulse.pulse / 8, pulse.pulse / 8);
//   ellipse(250, 80, pulse.pulse / 4, pulse.pulse / 4);
// }



var xspacing = 16;    // Distance between each horizontal location
var w;                // Width of entire wave
var theta = 0.0;      // Start angle at 0
var amplitude = Math.floor((Math.random() * 200) + 180); // Height of wave
var target_amplitude = 0;
var current_amplitude = 0;
var period = 70.0;   // How many pixels before the wave repeats
var dx;               // Value for incrementing x
var yvalues;  // Using an array to store height values for the wave
var previous = pulse.previousVariance;
var MAX_DELTA = 1;

function setup() {
  // createCanvas(710, 400);
    var myCanvas = createCanvas(windowWidth, windowHeight);
    myCanvas.parent('display');
  w = width+16;
  dx = (TWO_PI / period) * xspacing;
  yvalues = new Array(floor(w/xspacing));
  console.log(yvalues);
}

function draw() {
  background(39, 39, 39);
  target_amplitude = pulse.variance;
  if (isNaN(current_amplitude)) {
    current_amplitude = target_amplitude;
  } else if (target_amplitude < current_amplitude) {
    var delta = Math.min(MAX_DELTA, current_amplitude - target_amplitude);
    current_amplitude -= delta;
  } else {
    current_amplitude += Math.min(MAX_DELTA, target_amplitude - current_amplitude);
  }
  period = pulse.bpm;
  calcWave();
  renderWave();
}

function calcWave() {
  // Increment theta (try different values for
  // 'angular velocity' here)
  theta += 0.02;

  // For every x value, calculate a y value with sine function
  var x = theta;
  for (var i = 0; i < yvalues.length; i++) {
    // console.log('BEFORE', yvalues);
    // yvalues[i] = lerp((sin(x)*previous), (sin(x)*amplitude), 0.2);
    yvalues[i] = sin(x)*current_amplitude;
    // console.log('AFTER', yvalues);
    x+=dx;
  }
}

function renderWave() {
  noStroke();
  // if (pulse.pulse > 512) {
  //   fill(105, 116, 124);
  // } else {
  //   fill(203, 255, 77);
  // };
  // fill(203, 255, 77));
  // fill(255);
  // A simple way to draw the wave with an ellipse at each location
  for (var x = 0; x < yvalues.length; x++) {
    if (x % 2 === 0) {
      fill(105, 116, 124);
    } else if (x % 3 === 0){
      fill(203, 255, 77);
    } else {
      fill(107, 170, 117);
    };

    // if (x % 2 === 0) {
    //   fill(189, 173, 234);
    // } else if (x % 2 !== 0){
    //   fill(190, 162, 194);
    // } else if (x % 3 === 0){
    //   fill(67, 129, 193);
    // } else {
    //   fill(163, 120, 113);
    // };
    ellipse(x*xspacing, height/2+yvalues[x], 16, 16);
  }
}
