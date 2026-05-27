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