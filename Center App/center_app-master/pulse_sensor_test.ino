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

void setup(){

  // Start Serial
  Serial.begin(115200);

  // Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();
}

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
