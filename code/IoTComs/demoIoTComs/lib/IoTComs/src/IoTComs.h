#ifndef IoTComs_H
#define IoTComs_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <ArduinoJson.h>

void requestGET(HTTPClient &https);
void requestPOST(HTTPClient &https, String jsonPayload);

#endif