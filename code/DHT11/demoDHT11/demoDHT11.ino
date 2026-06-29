#include <Arduino.h>
#include "DHT.h"

/*
 This is a demo for the DHT11 Component
*/

/// Parameters
#define DHTPIN 4 // Modify pins if necessary
#define DHTTYPE DHT11

float valTemp = 0;
float valHumid = 0;
float indexHeat = 0;

// Lib Init
DHT dht(DHTPIN, DHTTYPE);

/// Code
// Function Declerations
void error(value){
  if(isnan(value)){
    Serial.println(F("Failed to read from DHT Sensor"));
    return;
  }
}

void readTemp(){
  valTemp = dht.readTemperature();
  error(value);
}

void readHumid(){
  valHumid = dht.readHumidity();
  error(value);
}

void calcHeatIndex(){
  indexHeat = dht.computeHeatIndex(valueTemp, valueHumid, false);
}

void printData(){
  Serial.print(F("Humidity: "));
  Serial.print(valueHumid);
  Serial.print(F("%  Temperature: "));
  Serial.print(valueTemp);
  Serial.print(F("°C "));
  Serial.print(F("°F  Heat index: "));
  Serial.print(heatIndex);
  Serial.print(F("°C "));
}
// Setup
void setup(){
  Serial.begin(115200); // Init Serial Monitor
  dht.begin(); // Init DHT
}

// Loop
void loop(){
  delay(2000); // Wait a few seconds between cycles

  // Self Explanatory
  readTemp();
  readHumid();
  printData();
}