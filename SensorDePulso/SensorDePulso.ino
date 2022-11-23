
/* Sensor de pulso
  Proyecto 3
  Angel Castellanos 21700
  Mario Cristales 21631
  Javier Ramirez 21600
  Jose Santisteban 21153
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true  // Se define el nivel de interrupcion de la libreria para el sensor de pulso
#include <PulseSensorPlayground.h>   // Se incluye la libreria del sensor de pulso

//  Variables
const int photocellPin = A1;       // Se define el pin de la fotocelda
const int PulseWire = 0;  // Se define el pin del sensor de pulso
const int LED5 = 05;      // Se define el pin del LED
int Threshold = 515;      // Se define el umbral del sensor de pulso

int touchInput = 3;      // Se define el pin del sensor de toque
int inputState;         // Se define la variable para el estado del sensor de toque
int dt = 100;          // Se define el tiempo de espera para el sensor de toque
int myBPM;            // Se define la variable para el pulso
int luminosidad = 0; // Se define la variable para la luminosidad

PulseSensorPlayground pulseSensor;  // Se crea el objeto para el sensor de pulso


void setup() {

  Serial.begin(9600);  // Se inicia la comunicacion serial
  pinMode(photocellPin, INPUT); // Se define el pin de la fotocelda como entrada

  // Se inicia el sensor de pulso
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED5);  
  pulseSensor.setThreshold(Threshold);
  pinMode(touchInput, INPUT);

  delay(200);

}



void loop() {
  inputState = digitalRead(touchInput); // Se lee el estado del sensor de toque
  delay(20);
  if (inputState == HIGH) { // Si el sensor de toque esta presionado
    
    while (inputState == HIGH) { // Una vez presionado el sensor de toque se lee el puslo hasta que se vuelva a presionar

      luminosidad = analogRead(photocellPin); // Se lee la luminosidad
      Serial.print(luminosidad); // Se imprime la luminosidad
      Serial.print(","); // Se imprime una coma para separar los datos
      myBPM = pulseSensor.getBeatsPerMinute();  // Se lee el pulso y se guarda en la variable myBPM
      

      Serial.print(myBPM);  // Se imprime el pulso
      Serial.println("a"); // Se imprime una a para separar los datos
      delay(500);


      inputState = digitalRead(touchInput); // Se lee el estado del sensor de toque
      delay(200);
      if (inputState == LOW) { //Si el sensor no se toca no sucede nada, por esto se debe seguir dentor del loop
        inputState = 1;
      } else {
        inputState = 0; // Si el sensor se toca se sale del loop
        break;
      }
    }
  }
}
