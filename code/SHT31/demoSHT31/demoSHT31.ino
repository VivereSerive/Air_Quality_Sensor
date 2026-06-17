#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

/*
The purpose of this example sketch is to test the SHT31 Sensor
*/

// SHT31 Parameters
float sTemp = 0; // SHT31 Temp
float sHumid = 0; // SHT31 Humidty

bool enableHeater = false;
uint8_t loopCnt = 0;

#define SHT31addr = 0x44; // Change to another I2C Address if needed

// Init Lib
Adafruit_SHT31 SHT31 = Adafruit_SHT31(); // Init Adafruit SHT31 Obj lib

// Function Declerations
void locateSHT31() {
  Serial.println("locating [SHT31] Module...");
  if (!SHT31.begin(SHT31addr)) {
    Serial.println("[SHT31]... Not Found");
    while(1) delay(1);
  } else {
    Serial.println("[SHT31]... Found");
  }
}

void checkHeaterState(){
  Serial.println("[SHT31] Heater State: ");
  If SHT31.isHeaterEnabled(){
    Serial.print("ENABLED");
  } else {
    Serial.print("DISABLED");
  }
}

void displayTemp(sTemp){
  // Check if 'not a number'
  if (!isnan(sTemp)){
    Serial.println("[SHT31]... Temp: ");
    Serial.print(sTemp);
    Serial.print("°C");
    Serial.print("\t\t");
  } else {
    Serial.println("[SHT31]... Failed to read temperature");
  }
}

void displayHumid(sHumid){
  // Check if 'not a number'
  if (!isnan(sHumid)){
    Serial.println("[SHT31]... Humid: ");
    Serial.print(sHumid);
    Serial.print("%");
    Serial.print("\t\t");
  } else {
    Serial.println("[SHT31]... Failed to read Humidity");
  }
}

void toggleHeater(){
  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30){
    enableHeater = !enableHeater;
    SHT31.heater(enableHeater);
    checkHeaterState();
    loopCnt = 0;
  } 
}

// Setup
void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // SHT31 Init Checks
  locateSHT31();
  checkHeaterState();
};

// Main Loop
void loop() {
  // Get Sensor Data
  sTemp = SHT31.readTemperature();
  sHumid = SHT31.readHumidity();

  // Display Data
  displayTemp();
  displayHumid();

  delay(1000);

  // Toggle Heater State
  toggleHeater();
  loopCnt++;
}