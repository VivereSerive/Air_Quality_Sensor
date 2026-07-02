#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "IoTComs.h"
#include "simpleSensors.h"

/// Parameters
// WiFi Details
const char* ssid = ""; // WiFi Name
const char* ssidKey = ""; // WiFi Password

// API Details
const char* server = ""; // Import server e.g. https://<computer_ip>:<flask_port>/flask_path
const char* sCertificate = ""; // Import server certificate
const char* sClientKey = ""; // Import server client key
const char* sPrivateKey = ""; // Import server private key

// TImers
unsigned long tLastTime = 0; 
unsigned long requestDelay = 30000; // 30 second request timer

// Sensor Pins
#define pinMQSensor 12 // Modify as necessary
#define pinDHTSensor 13 // Modify as necessary

// Sensor Variable Declerations
#define typeDHT DHT11 // Modify as necessary

float valueMQ = 0;
float valueTemp = 0;
float valueHumid = 0;
float valueHeatIndex = 0; 

/// Code
// Function Declerations
void packageSensorData(JsonDocument &payload, float dataMQ, float dataTemp, float dataHumid, float dataHeatIndex){
  payload["MQ Data"] = dataMQ;
  payload["Temp C"] = dataTemp;
  payload["Humid %"] = dataHumid;
  payload["Heat Index"] = dataHeatIndex;
}

// Setup
void setup(){
  Serial.begin(115200); // Init Serial Monitor
  Serial.println();

  // Init JSON payload
  JsonDocument payload;

  // Init ESP32 WiFi
  Serial.print("Attempting Connection To:");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, ssidKey);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  // Success
  Serial.print("Connected: ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
}

// Loop
void loop(){  
  // Check Execution TImer
  if ((millis() -tLastTime >= requestDelay) || tLastTime == 0){
    Serial.println("Initializing Data Collection");
    // Data Collection
    DHT dht(pinDHTSensor, typeDHT); // Init Lib Obj
    readTemp(valueTemp, dht);
    readHumid(valueHumid, dht);
    readMQGas(valueMQ, pinMQSensor);
    calcHeatIndex(valueHeatIndex, valueTemp, valueHumid, dht);

    // Send Data to Server
    if (WiFi.status() == WL_CONNECTED){
      WiFiClientSecure *client = new WiFiClientSecure; // Init lib obj
      if (client){
        // Securing Client
        // client->setCACert(sCertificate);
        // client->setInsecure(); // Bypasses verification
        client->setCertificate(sClientKey);
        client->setPrivateKey(sPrivateKey);

        HTTPClient https; // Init lib obj
        JsonDocument packagedData; // Init ArduinoJSON lib obj
        String payload; 
        packageSensorData(packagedData, valueMQ, valueTemp, valueHumid, valueHeatIndex);
        serializeJsonPretty(packagedData, payload); // Convert JSON document to String

        // Init Secure Client HTTPS Communication
        // Begin Requests
        Serial.print("[HTTPS] begin... \n");
        if (https.begin(*client, server)){
          // requestGET (https); // GET Request Method
          requestPOST(https, payload);
        }
        
        delete client; // Frees memory, Prevents memory leaks and crashes
        packagedData.clear(); // Reset Payload for next data package
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
    tLastTime = millis(); // Reset execution timer
    Serial.println("Data Collection Finished");
  }

  // Cooldown
  Serial.println("On Cooldown");
  delay(1000);
  Serial.println(".");
}