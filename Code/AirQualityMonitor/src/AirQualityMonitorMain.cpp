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

        // Init an HTTPS connection using the secure client
        Serial.print("[HTTPS] begin...\n");
        if(https.begin(*client, SERVER_PATH)){ // HTTPS

            int httpCode = https.GET();
            if (httpCode > 0){

            }
        }else{
            Serial.printf("[HTTP] METHOD... failed, error %s\n", https.errorToString(httpCode).c_str);
        }
        https.end();
    }else{
        Serial.println("[HTTPS] Unable to connect\n"); // Error response
    }
    Serial.println();
    Serial.println("Waiting 2min before the next round...");
    delay(120000);
}