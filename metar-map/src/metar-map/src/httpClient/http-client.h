#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "../weather/weatherStation.h"

#define STATION_NAME "icaoId"

String makeGetCall(String);
void parseResponse(String, WeatherStation (&)[], uint8_t);