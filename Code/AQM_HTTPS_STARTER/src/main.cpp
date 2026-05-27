#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

/*
  HTTPS Starter from: https://randomnerdtutorials.com/esp32-https-requests/#what-is-https
  The focus of this sketch is for me to bash my head against 
  communication with commuciating Flask API with ESP32
*/

// WiFi Details
const char* ssid = ""; //! WiFi name
const char* ssid_password = ""; //! WiFi password

// API Details
const char* server = ""; //! Domain Server e.g. "http://<computer_ip>:<flask_port>/flask_path"

// Not using 
const char* test_root_ca= ""; //! Plug here server's root certification authority (root CA)

// Init WiFiClientSecure
WiFiClientSecure client; 

void setup(){
  Serial.begin(115200); // Init Serial Monitor
  delay(100); // Wait for port to open

  // Connection to WiFi...
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, ssid_password);

  // Attempt to connect
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000); // Wait before retrying
  }

  // Success Response
  Serial.print("Connected to: ");
  Serial.println(ssid);

  // Verifying client
  client.setCACert(test_root_ca);

  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443)){
    Serial.println("Connection Failed!");
  }else{
    Serial.println("Connected to Server!");

    // Make a HTTP POST
    // String jsonPayload = "{\"message\": \"hello world\"}";

    // client.println("POST /your_flask_path HTTP/1.1");
    // client.println(String("Host: ") + server);
    // client.println("Content-Type: application/json");
    // client.println("Connection: close");
    // client.println(String("Content-Length: ") + jsonPayload.length());
    // client.println(); // Blank line required — separates headers from body
    // client.println(jsonPayload);

    // // Wait for and print the response
    // while (client.connected()) {
    //   String line = client.readStringUntil('\n');
    //   Serial.println(line);
    //   if (line == "\r") break; // End of headers
    // }
    // String response = client.readString();
    // Serial.println("Response body: " + response);
    
    // Free client
    client.stop();
  }
}
