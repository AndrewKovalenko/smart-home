#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "../utils/stringUtils.h"
#include "../weather/stationsToLed.h"

String makeGetCall(String);
void parseResponse(String, WeatherStation (&)[], uint8_t);