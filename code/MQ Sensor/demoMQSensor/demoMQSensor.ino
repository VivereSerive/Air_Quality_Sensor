#include <Arduino.h>

/*
  This is a demo for the MQ Sensor to showcase the code necessary for the module
  WARNING: Sensor requires HEATING for half an hour to have reliable results
*/

/// Parameters
#define MQ_PIN 13 // Change if necessary
float valueGas = 0;

/// Code
// Function Declerations
void readGas(PIN){
  valueGas = analogRead(PIN);
}

// Setup
void setup(){
  Serial.begin(115200); // Init Serial Monitor
}

// Loop
void loop(){
  delay(2000); // Wait Between Readings
  readGas(MQ_PIN);
  Serial.print("Gas Level");
  Serial.println(valueGas)
}