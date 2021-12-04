#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "../utils/stringUtils.h"

typedef struct StationWeather
{
    String stationName;
    String weather;
};


String makeGetCall(String);
void parseResponse(String, StationWeather (&)[]);