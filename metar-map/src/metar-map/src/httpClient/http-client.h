#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "../utils/stringUtils.h"
#include "../weather/weatherStation.h""

String makeGetCall(String);
void parseResponse(String, WeatherStation (&)[], uint8_t);