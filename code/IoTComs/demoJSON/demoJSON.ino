#include <Arduino.h>
#include <ArduinoJson.h>

/*
  This sketch is to demonstrate packaging data into JSON payload.
*/

//// Parameters
// Readings
int rCo2 = 500;
int rPM = 1500;
int rHumid = 57;
int rTemp = 21;

//// Code
// Function Declerations

// Setup
void setup(){
  Serial.begin(115200);

  // JSON Payload
  JsonDocument payload;

  // Sensor Readings JSON Payload
  payload["Carbon Dioxide"] = rCo2;
  payload["Particulate Matter"] = rPM;
  payload["Humidity"] = rHumid;
  payload["Temperature"] = rTemp;

  // Print
  serializeJson(payload, Serial);
  Serial.println();
}

// Main
void loop(){
}