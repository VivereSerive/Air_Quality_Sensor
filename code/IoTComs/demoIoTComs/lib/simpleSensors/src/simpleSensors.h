#ifndef simpleSensor_H
#define simpleSesnor_H

#include <Arduino.h>
#include <DHT.h>

// DHT Sensor Functions
void readTemp(float storage, DHT &dht){
}

void readHumid(float storage, DHT &dht){
}

void calcHeatIndex(float storage, float temp, float humid, DHT &dht){
}

void printDHT(float humid, float temp, float heatIndex){
}

// MQ Sensor Functions
void readMQGas(float storage, int PIN){
}

#endif