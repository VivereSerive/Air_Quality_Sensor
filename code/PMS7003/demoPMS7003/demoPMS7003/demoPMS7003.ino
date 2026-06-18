#include <Arduino.h>
#include "PMS.h"

/*
 PMS7003 Demo Sketch using the PMS Library 
 https://github.com/fu-hsi/PMS/tree/master/examples
 https://anyapava.medium.com/pms7003-esp32-133ea9ee4be8
*/

//// Parameters
// PMS7003 TX/RX GPIO swap if needed
# define pmsTX 16;
# define pmsRX 17;

//// Init Lib Obj
// PMS7003
PMS pms(Serial);
PMS:DATA data;

//// Code
// Setup
void loop(){
  Serial.begin(115200); // Init Serial Monitor

  // Init Serial2 for the PMS7003
  // as it is the default for the component
  Serial2.begin(9600, SERIAL_8N1, pmsTX, pmsRX);
  pms.begin(Serial2);
}

// Loop
void loop(){
  if (pms.read(data)){
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM10_UG);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM25_UG);
    Serial.print("PM 10 (ug/m3): ");
    Serial.println(data.PM100_UG);
    Serial.println();
  }
  delay(1000);
}