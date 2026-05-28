#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

/*
    Started: 29/05/26

    This sketch will be the culmination of the starter sketches that I have made.

    Basically, this will be the main project folder of the code that the outcome
    will need.
*/

//* Variable Declerations

// WiFi Details
const char* SSID = ""; // WiFi name
const char* SSID_PASS = ""; // WiFi password

// API Details
const char* SERVER = ""; // SERVER url e.g. http://<computer_ip>:<flask_port>
const char* SERVER_PATH = ""; // SERVER PATH e.g.  http://<computer_ip>:<flask_port>/flask_path
const char* API_KEY = ""; // API KEY must match with the API
const char* API_CERTIFICATE = ""; // CERTIFICATE must match with the API
const char* API_PRIVATE_KEY = ""; // PRIVATE KEY must match with the API

// Variable Delcerations
const char* JSON_PAYLOAD = "{\"test_string\":\"Hello World!\",\"test_int\":\"12345\"}"; // placeholder

// Init WiFiClientSecure
WiFiClientSecure client; // Init WiFiClientSecure

//* Function Declerations

//* Code runs here
void setup(){
    Serial.begin(115200); // Init Serial Monitor
    delay(100); // Await port open

    // Init WiFi
    Serial.println("Attempting Connection: ");
    Serial.println(SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, SSID_PASS);

    // Attempt to connect
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(1000); // Wait before retrying
    }

    // Success Response
    Serial.print("Connected to: ");
    Serial.println(SSID);
    Serial.print("WiFi IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){
    WiFiClientSecure *client = new WiFiClientSecure; // Init WiFiClientSecure
    if (client){
        // Securing Client
        client->setCertificate(API_CERTIFICATE);
        client->setPrivateKey(API_PRIVATE_KEY);

        HTTPClient https; // Init HTTPClient

        // Init HTTPS & Secure Client Communication
        Serial.print("[HTTPS] begin...\n");
        
        // ### Begins
        if (https.begin(*client, SERVER_PATH)){
            // HTTPS GET Request
            Serial.println("[HTTPS] GET...\n");
            int httpCode = https.GET(); // Start Connection and send HTTP Header
            
            // Handles error and success response
            if (httpCode > 0){ // Error will be negative
                Serial.printf("[HTTPS] GET... code: %d\n"); // HTTP & Server response header has been sent and handled
                // file found at server
                if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
                    String payload = https.getString();
                    Serial.println(payload);
                }
            }else{
                Serial.printf("[HTTPS] GET... failed, error: %s/n", https.errorToString(httpCode).c_str());
            }
            https.end();
        }
        // ### Ends
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
    Serial.println();
    Serial.println("Waiting 2min before the next round...");
    delay(120000);
}