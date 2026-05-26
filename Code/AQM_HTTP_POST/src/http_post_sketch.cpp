#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

/*
  This ESP32 Sketch will be me trying to connect an ESP32 to a simple Web API
  Using only local WiFi & a computer (no live server business, im broke) and sending data to the API

  Reference: https://randomnerdtutorials.com/esp32-http-get-post-arduino/
*/

//####//

// API Key 
const char* API_KEY = "C7r57niMC6PFQXebcymAFLCdGGRRNGyM"; // Must be the same in the API

// WiFi Details
const char* ssid = ""; //! Replace with your WiFi Network
const char* ssid_pass = ""; //! Replace with your WiFi Network Password

String server_name = ""; //! Replace with computer ip and flask port "http://<computer_ip>:<flask_port>/flask_path" 

// Timers
unsigned long last_time = 0; 
// unsigned long timer_delay = 600000; // Sends a request every 10 minutes  
unsigned long timer_delay = 5000; // Sends a request every 5 seconds

//####//

void setup() {
  // Setup
  Serial.begin(115200);
  WiFi.begin(ssid, ssid_pass);

  // Connecting to Server
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

//####//

void loop() {
  // Send the request based on timer delay
  if ((millis() - last_time) > timer_delay){
    if(WiFi.status() == WL_CONNECTED){ // Checks connection status
      WiFiClient client; // Init WiFiClient
      HTTPClient http; // Init HTTPClient

      //* Sends an HTTP POST Request
      http.begin(client, server_name); // Init connection to flask app
      http.addHeader("Content-Type", "application/json");  // Specify Content Type Header as JSON object
      http.addHeader("AQM-API-KEY", API_KEY); // Custom API KEY header
      int httpResponseCode = http.POST("{\"test_string\":\"Hello World!\",\"test_int\":\"12345\"}"); // POST the JSON file

      // Status Feedback
      if (httpResponseCode > 0){ // Server response, 200, 400, 401, 500
        Serial.printf("HTTP Response Code: %d\n", httpResponseCode);
        Serial.println("Message: " + http.errorToString(httpResponseCode));
      } else { // Connection Failure
        Serial.printf("Connection Failure! Code: %d\n", httpResponseCode);
        String response_msg = http.getString();
        Serial.println("Message: " + http.errorToString(httpResponseCode));
      }

      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      // Free Resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    last_time = millis();
  }
}