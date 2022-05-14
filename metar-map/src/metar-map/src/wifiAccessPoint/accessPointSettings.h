#ifndef _WIFI_AP_SETTINGS_
#define _WIFI_AP_SETTINGS_

#include <ESP8266WiFi.h>

const char ACCESS_POINT_SSID[] = "metar_map";
const char ACCESS_POINT_PASSWORD[] = "metarmappass";
const int ACCESS_POINT_CHANEL = 12;
const int MAX_ACCESS_POINT_CONNECTIONS = 1;

const IPAddress local_IP(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

#endif