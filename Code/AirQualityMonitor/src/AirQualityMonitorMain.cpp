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
const char* SERVER = "www.howsmyssl.com"; // SERVER url e.g. http://<computer_ip>:<flask_port> or www.domain.com
const char* SERVER_PATH = "https://www.howsmyssl.com/a/check"; // SERVER PATH e.g.  http://<computer_ip>:<flask_port>/flask_path or https://www.domain.com/path
const char* API_KEY = ""; // API KEY must match with the API
const char* API_CERTIFICATE = ""; // CERTIFICATE must match with the API
const char* API_PRIVATE_KEY = ""; // PRIVATE KEY must match with the API
const char* rootCACertificate = \
    "-----BEGIN CERTIFICATE-----\n" \
    "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\n" \
    "-----END CERTIFICATE-----";

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
        // client->setCertificate(API_CERTIFICATE);
        // client->setPrivateKey(API_PRIVATE_KEY);
        client->setCACert(rootCACertificate);
        
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