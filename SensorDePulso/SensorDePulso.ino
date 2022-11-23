
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks LED on PIN 13 with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true  // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>   // Includes the PulseSensorPlayground Library.

//  Variables
const int photocellPin = A1;
int val = 0;
const int PulseWire = 0;  // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED5 = 05;      // The on-board Arduino LED, close to PIN 13.
int Threshold = 515;      // Determine which Signal to "count as a beat" and which to ignore.
                          // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                          // Otherwise leave the default "550" value.

int touchInput = 3;
int inputState;
int lastInputState = 1;
int dt = 100;
int myBPM;
int luminosidad = 0;

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {

  Serial.begin(9600);  // For Serial Monitor
  pinMode(photocellPin, INPUT);
  // Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED5);  //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  pinMode(touchInput, INPUT);

  delay(200);
  // Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
      //This prints one time at Arduino power-up,  or on Arduino reset.
  }
}



void loop() {
  inputState = digitalRead(touchInput);
  delay(20);
  if (inputState == HIGH) {
    int valorMax = 140;
    int valorMin = 40;
    // "myBPM" hold this BPM value now.
    while (inputState == HIGH) {

      luminosidad = analogRead(photocellPin);
      Serial.print(luminosidad);
      Serial.print(",");
      myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                // "myBPM" hold this BPM value now.

      // "myBPM" hold this BPM value now.


      Serial.print(myBPM);  // Print the value inside of myBPM.
      Serial.println("a");
      delay(500);


      inputState = digitalRead(touchInput);
      delay(200);
      if (inputState == LOW) {
        inputState = 1;
      } else {
        inputState = 0;
        break;
      }
    }
  }
}
