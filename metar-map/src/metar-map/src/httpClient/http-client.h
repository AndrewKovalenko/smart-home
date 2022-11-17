#include <Arduino.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClientSecureBearSSL.h>
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "../weather/weatherStation.h"

#define STATION_PROPERTY_NAME "stationId"
#define FLIGHT_CATEGORY_PROPERTY_NAME "flightCategory"
#define MAX_SUPPORTED_REQUEST_SIZE 2048

String makeGetCall(String);
void parseResponse(String, WeatherStation *, uint8_t);