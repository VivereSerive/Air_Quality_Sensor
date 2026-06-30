#include "IoTComs.h"

void requestGET(HTTPClient &https){
    // GET Request 
    Serial.println("[HTTPS] GET...\n");
    int httpCode = https.GET(); // start connection & send HTTP header

    // File Found at Server
    if (httpCode > 0){
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode); // HTTP header sent and Server response header handled
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

void requestPOST(HTTPClient &https, String jsonPayload){
    // POST Request Method
    Serial.println("[HTTPS] POST... \n"); 
    https.addHeader("Content-Type", "application/json"); // Specificy Content Type Header
    int httpsResponseCode = https.POST(jsonPayload); // start the connection & send the request

    // Handles Response
    if (httpsResponseCode > 0){
        Serial.printf("[HTTPS] POST... code: %d\n", httpsResponseCode);
    } else{
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpsResponseCode).c_str());
    }
    https.end();
}