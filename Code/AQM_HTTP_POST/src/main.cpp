#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

/*
  This ESP32 Sketch will be me trying to connect an ESP32 to a simple Web API
  Using only local WiFi & a computer (no domain business) and sending data to the API

  Reference: https://randomnerdtutorials.com/esp32-http-get-post-arduino/
*/

//####//

// WiFi Details
const char* ssid = ""; // Replace with your WiFi Network
const char* ssid_pass = ""; // Replace with your WiFi Network Password

String server_name = ""; // Replace with computer ip and flask port "http://<computer_ip>:<flask_port>/flask_path" 

// Timer
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
      // Init HTTPClient
      HTTPClient http;

      // Sends an HTTP POST Request
      // TODO: Send a JSON containing the string "Hello World"
      String server_path = server_name + "";
      http.begin(server_path.c_str());


      // TODO: Create Error Feedback 


      // Free Resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    last_time = millis();
  }
}