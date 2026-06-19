#include <Arduino.h>
#include <S8_UART.h>

//// Parameters
// SenseairS8 GPIO Pins (Configure as necessary)
#define co2RX 13
#define co2TX 12

//// Init Lib Obj
S8_UART co2Sensor(Serial1);

//// Code
// Function Declerations
func readCo2(){
  int co2Readings = co2Sensor.get_co2();

  if(co2 >= 0){
    Serial.print("CO2 Concentration: ");
    Serial.print(co2);
    Serial.println(" ppm");
  } else {
    Serial.println("Error reading sensor!");
  }

  delay(1000); 
}

// Setup
void setup(){
  Serial.begin(115200);
  
  // Init Serial1 for the SenseairS8 with a baude rate
  // of 9600 as it is the default for the component
  Serial1.begin(9600, SERIAL_8N1, co2RX, co2TX);
}

// Main
void loop(){
  readCo2();
}