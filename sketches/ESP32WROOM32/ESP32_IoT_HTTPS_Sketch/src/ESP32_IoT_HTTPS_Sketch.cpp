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
String jsonCigMetric = "{\"cig_smoked_per_capita\":[30.34, 18.2, 18.24, 25.82, 28.6, 31.1, 40.46, 33.6, 28.27, 20.1, 27.91, 26.18, 22.12, 21.84, 23.44, 21.58, 26.92, 25.91, 28.92, 24.96, 22.06, 27.56, 16.08, 23.75, 23.32, 19.96, 42.4, 28.64, 21.16, 29.14, 26.38, 23.44, 23.78, 29.18, 18.06, 20.94, 20.08, 22.57, 14.0, 25.89, 21.17, 21.25, 22.86, 28.04]}";
String jsonDeathMetric = "{\"deaths_per_1000_from_lung_cancer\":[25.88, 17.05, 15.98, 19.80, 22.07, 22.83, 27.27, 24.55, 23.57, 13.58, 22.80, 20.30, 16.59, 16.84, 17.71, 25.45, 22.04, 26.48, 20.94, 22.72, 14.20, 20.98, 15.60, 19.50, 16.70, 12.12, 23.03, 25.95, 14.59, 25.02, 21.89, 19.45, 12.11, 23.68, 17.45, 14.11, 17.60, 20.74, 12.01, 21.22, 20.34, 20.55, 15.53, 15.92]}";

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

//* #### Function Declerations
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

//* #### Setup
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

//* #### Main Loop
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
        // Begin Requests
        Serial.print("[HTTPS] begin... \n");
        if (https.begin(*client, server)){
          // GETRequest(https); // GET Request Method
          POSTRequest(https);
        }
        delete client; // Frees memory, Prevents memory leaks and crashes
      }
    } else {
      Serial.println("WiFi Disconnected");
    }
    tLastTime = millis(); // Reset execution timer
  }
}