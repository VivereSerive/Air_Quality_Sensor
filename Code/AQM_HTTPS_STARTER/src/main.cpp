#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

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
const char* test_client_key = \
  "-----BEGIN PRIVATE KEY-----\n" \
  "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\n" \
  "HcDn68CCdH5qGJaKAS+/txaLoS8E\n" \
  "-----END PRIVATE KEY-----\n";

const char* test_client_cert = \
  "-----BEGIN CERTIFICATE-----\n" \
  "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\n" \
  "pzdPaDvFcd+f2Ed2\n" \
  "-----END CERTIFICATE-----\n";

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

  // Verifying API
  

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
