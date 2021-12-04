#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

String makeGetCall(String);
void parseResponse(String, String (&)[]);