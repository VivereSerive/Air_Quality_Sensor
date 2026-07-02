#include "simpleSensors.h"

// DHT Sensor Functions
void readTemp(float storage, DHT &dht){
    storage = dht.readTemperature();
    if(isnan(storage)){
        Serial.printf("Failed to read from DHT Sensor");
        return;
    }
}

void readHumid(float storage, DHT &dht){
    storage = dht.readHumidity();
    if(isnan(storage)){
        Serial.printf("Failed to read from DHT Sensor");
        return;
    }
}

void calcHeatIndex(float storage, float temp, float humid, DHT &dht){
    storage = dht.computeHeatIndex(temp, humid, false); // false = Celcius, true = Fahrenheit
}

void printDHT(float humid, float temp, float heatIndex){
    Serial.print(F("Humidity: "));
    Serial.print(humid);
    Serial.print(F("%  Temperature: "));
    Serial.print(temp);
    Serial.print(F("°C "));
    Serial.print(F("°F  Heat index: "));
    Serial.print(heatIndex);
    Serial.print(F("°C "));
}

// MQ Sensor Functions
void readMQGas(float storage, int PIN){
    storage = analogRead(PIN);
}