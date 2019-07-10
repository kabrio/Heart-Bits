volatile int rate[10];        // holds last 10 IBI values
volatile unsigned long sampleCounter = 0;     // determines pulse timing
volatile unsigned long lastBeatTime = 0;      // used to find IBI
volatile int P = 512;         // peak in pulse wave, seeded
volatile int T = 512;         // trough in pulse wave, seeded
volatile int thresh = 512;        // pulse is found when signal exceeds thresh
volatile int amp = 100;           // holds amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;  // seeds rate array
volatile boolean secondBeat = false; // seeds rate array

// Variables from pulse_sensor_test
// ================================
// Sensor and pins variables
int pulsePin = 0;
int blinkPin = 13;

// Pulse rate variable
volatile int BPM;

// Raw signal
volatile int Signal;

// Interval between beats
volatile int IBI = 600;

// Becomes true when the pulse is high
volatile boolean Pulse = false;

// Becomes true when Arduino finds a pulse
volatile boolean QS = false;

// ================================

// pulse_sensor_test function:
// ===========================
void setup(){

  // Start Serial
  Serial.begin(115200);

  // Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();
}

// ==============================

// Timer to take a reading every 2 miliseconds
void interruptSetup(){
  // initializes Timer2: throws an interrupt every 2ms
  TCCR2A = 0x02;      // disable pwm on digital pins 3 and 11 and go into CTC mode
  TCCR2B = 0x06;      // don't force compare, 256 prescaler
  OCR2A = 0X7C;       // set the top of the count to 124 for 500hz sample rate
  TIMSK2 = 0x02;      // enable interrupt on match between Timer2 and OCR2A
  sei();              // make sure global interrupts are the enabled
}

// Timer2 INTERRUPT SERVICE ROUTINE
ISR(TIMER2_COMPA_vect){             // triggered when Timer2 counts to 124
  cli();                            // disable interrupts while we do this
  Signal = analogRead(pulsePin);    // read the pulse sensor
  sampleCounter += 2;               // this var keeps track of time in mS
  int N = sampleCounter - lastBeatTime;   // monitors time since the last beat to avoid noise

// find peak and trough
  if(Signal < thresh && N > (IBI/5)*3){   // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                      // T is the trough
      T = Signal;                         // keep track of lowest point in pulse wave
    }
  }
  if(Signal > thresh && Signal > P){    // thresh condition helps avoid noise
    P = Signal;                         // P is the peak
  }                                     // keep track of highest point in pulse wave

// look for the heart beat (every time signal surges above threshold)
  if (N > 250){                // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){
      Pulse = true;           // set the Pulse flag when we think there is a pulse
      digitalWrite(blinkPin,HIGH);      // turn on pin 13 LED
      IBI = sampleCounter - lastBeatTime;   // measure time between beats in mS
      lastBeatTime = sampleCounter;         // keep track of time for next pulse

      if(secondBeat){        // if this is the second beat, if secondBeat == TRUE
        secondBeat = false;     // clear secondBeat flag
        for(int i=0; i<=9; i++){    // seed the running total to get a realistic BPM at startup
          rate[i] = IBI;
        }
      }

      if(firstBeat){        // if it's the first time we found a beat, if firstBeat == TRUE
        firstBeat = false;    // clear firstBeat flag
        secondBeat = true;    // set the secondBeat flag
        sei();                // enable interrupts again
        return;              // IBI value is unreliable so discard it
      }

// running total of last 10 IBI values
      word runningTotal = 0;    // clear the runningTotal variable

      for(int i=0; i<=8; i++){    //shift data in the rate array
        rate[i] = rate[i+1];      //and drop the oldest IBI value
        runningTotal += rate[i];    // add up the 9 oldest IBI values
      }

      rate[9] = IBI;          // add the latest IBI to the rate array
      runningTotal += rate[9];    // add the latest IBI to runningTotal
      runningTotal /= 10;     // average the last 10 IBI values
      BPM = 60000/runningTotal;   // calculates BPM
      QS = true;            // set Quantified Self flag
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }
  }

  if (Signal < thresh && Pulse == true){    // when the values are going down, the beat is over
    digitalWrite(blinkPin,LOW);       // turn off pin 13 LED
    Pulse = false;          // reset Pulse flag so it's ready for next pulse
    amp = P - T;            // get amplitude of the pulse wave
    thresh = amp/2 + T;     // set thresh at 50% of the amplitude
    P = thresh;             // reset P & T for next pulse
    T = thresh;
  }

  if (N > 2500){            // if 2.5 seconds go by without a beat
    thresh = 512;           // set thresh default
    P = 512;                // set P default
    T = 512;                // set T default
    lastBeatTime = sampleCounter;   // update the lastBeatTime
    firstBeat = true;       // set these to avoid noise
    secondBeat = false;     // when we get the heartbeat back
  }

  // pulse_sensor_test function 2
  // ============================
  void loop(){

    // If heart beat is found
    if (QS == true) {

      // Print heart rate
      Serial.print("Heart rate: ");
      Serial.println(BPM);

      // Reset the Quantified Self flag for next time
      QS = false;
     }

    // Wait 20 ms
    delay(20);
  }
  // ==============================

  sei();                    // enable interrupts when you're done
}   // end ISR
