#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>

/*
  Getting around HTTPS & ESP32
  References:
    https://randomnerdtutorials.com/esp32-https-requests/
*/

// Variable Declerations

// WiFI Details
const char* ssidKey = ""; // Import WiFi password 
const char* ssid = ""; // Import WifI name

// TImers
unsigned long tLastTime = 0; 
unsigned long requestDelay = 120000; // 2 minute Request timer

// API Details
const char* server = ""; // Import server e.g. http://<computer_ip>:<flask_port>/flask_path
const char* sCertificate = ""; // Import server certificate
const char* sClientKey = ""; // Import server client key
const char* sPrivateKey = ""; // Import server private key

// Function Declerations
void GETRequest(){
  WiFiClientSecure *client = new WiFiClientSecure; // Init lib obj
  if (client){
    // Securing Client
    // client->setCACert(sCertificate);
    client->setCertificate(sClientKey);
    client->setPrivateKey(sPrivateKey);

    HTTPClient https; // Init lib obj

    // Init Secure Client HTTPS Communication
    Serial.print("[HTTPS] begin ...\n");

    // Begin Requests
    if (https.begin(*client, server)){
      // GET Request Method
      Serial.println("[HTTPS] GET...\n");
      int httpCode = https.GET(); // start connection & send HTTP header

      // Handles Server Responses
      if (httpCode > 0){ // Erros will be negative
        Serial.printf("[HTTPS] GET... code: %d\n"); // HTTP header sent and Server response header handled

        // File found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
          // Print server response
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error; %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  } 
  Serial.println();
  Serial.println("Waiting 2 minutes before next round...");
  delay(requestDelay);
}

// Setup
void setup(){
  Serial.begin(115200); // Init Serial Monitor
  Serial.println();

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

// Main Loop
void loop(){
  GETRequest();
}