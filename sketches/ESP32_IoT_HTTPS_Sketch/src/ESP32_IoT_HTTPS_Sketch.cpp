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
String jsonPayload = "{\"sensor\":\"temperature\",\"value\":25.5}"; // Import json file

// WiFI Details
const char* ssidKey = ""; // Import WiFi password 
const char* ssid = ""; // Import WifI name

// TImers
unsigned long tLastTime = 0; 
unsigned long requestDelay = 120000; // 2 minute Request timer

// API Details
const char* server = ""; // Import server e.g. https://<computer_ip>:<flask_port>/flask_path
const char* sCertificate = ""; // Import server certificate
const char* sClientKey = ""; // Import server client key
const char* sPrivateKey = ""; // Import server private key

// Function Declerations
void GETRequest(HTTPClient &https){
  // GET Request Method
  Serial.println("[HTTPS] GET...\n");
  int httpCode = https.GET(); // start connection & send HTTP header

  // Handles Server Responses
  if (httpCode > 0){ // Erros will be negative
    Serial.printf("[HTTPS] GET... code: %d\n", httpCode); // HTTP header sent and Server response header handled

    // File found at server
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
      // Print server response
      String payload = https.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
  }
  https.end();
}

void POSTRequest(HTTPClient &https){
  // POST Request Method
  Serial.println("[HTTPS] POST... \n"); 
  https.addHeader("Content-Type", "application/json"); // Specificy Content Type Header
  int httpsResponseCode = https.POST(jsonPayload); // start the connection & send the request

  // Handles Responses
  if (httpsResponseCode > 0){
    Serial.printf("[HTTPS] POST... code: %d\n", httpsResponseCode);
  }else {
    Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpsResponseCode).c_str());
  }
  https.end();
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

void loop(){
  if ((millis() -tLastTime >= requestDelay) || tLastTime == 0){
    if (WiFi.status() == WL_CONNECTED){
      WiFiClientSecure *client = new WiFiClientSecure; // Init lib obj
      if (client){
        // Securing Client
        // client->setCACert(sCertificate);
        // client->setInsecure(); // Bypasses verification
        client->setCertificate(sClientKey);
        client->setPrivateKey(sPrivateKey);

        HTTPClient https; // Init lib obj

        // Init Secure Client HTTPS Communication
        Serial.print("[HTTPS] begin... \n");

        // Begin Requests

        if (https.begin(*client, server)){
          GETRequest(https); // GET Request Method
        }
        delete client; // Frees memory, Prevents memory leaks and crashes
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
    tLastTime = millis(); // Reset execution timer
  }
}