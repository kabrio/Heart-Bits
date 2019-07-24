int dotsHue = 40; // Global variable

void setup() {
  size(800, 800);
  pixelDensity(displayDensity()); // For retina and other high res displays
  colorMode(HSB, 360, 100, 100); // HSB color mode for the win!
  println("hi!");
}

void draw() {  
  //background(0); 
  // println("hi again!");
  // A Trick: Fades out previous drawings.
  // Make a rectangle cover previous drawings...     
  // ...but fill it with 10% opacity only
  fill(0, 10);
  strokeWeight(0);
  rect(0, 0, width, height);

  // Placing points randomly, starting from center of screen.
  strokeWeight(random(40));
  stroke(dotsHue, random(30, 100), 100);
  // Local variables
  int centerX = width/2; // Center of x-axis 
  int centerY = height/2; // Center of y-axis 
  int area = 150; 
  point(centerX+random(-area, area), centerY+random(-area, area));
}

void keyPressed() {
  println("key was pressed, hooray!");
  if (key == 'x') {
    background(360);
    dotsHue = int(random(100, 300)); // Set a new random hue for points
  }
}
