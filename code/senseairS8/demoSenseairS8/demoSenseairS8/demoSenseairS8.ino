#include <Arduino.h>

/*
  This sketch is to test the SenseairS8 Co2 Sensor
  https://github.com/ghosty-be/esp32-senseair_s8
*/

//// Paramaters
// SenseairS8 GPIO Pins (Configure as necessary)
#define co2RX 13
#define co2TX 12

// Co2 Count
byte reqCo2[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};
byte outCo2[] = {0, 0, 0, 0, 0, 0, 0};

//// Code
// Function Declerations
void requestCo2(){
  while(!Serial1.available()){
    Serial.write(reqCo2, 7);
    delay(50);
  }

  int timeout = 0;
  while(Serial1.available() < 7){
    timeout++;
    if(timeout > 10){
      while(Serial1.available()){
        Serial1.read();
        break;
      }
    }
    delay(50);
  }
  
  for(int count = 0; count < 7; count++){
    outCo2[i] = Serial1.read();
  } 
}

unsigned long countCo2(){
  int high = outCo2[3];
  int low = outCo2[4];
  unsigned long val = high * 256 + low;
  return val * 1; // S8 = 1. K-30 3% = 3, K-33 ICB = 10
}

// Setup
void setup(){
  Serial.begin(115200); // Init Serial Monitor
  
  // Init Serial1 for the SenseairS8 with a baude rate
  // of 9600 as it is the default for the component
  Serial1.begin(9600, SERIAL_8N1, co2RX, co2TX);
}

// Main
void loop(){
  // Get & Display Data From Sensor
  requestCo2();
  unsigned long Co2 = CO2count();
  delay(2000);
  String Co2s = "Co2: " + String(Co2);
  Serial.prointln(Co2s);
}