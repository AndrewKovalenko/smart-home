#include <ESP8266WiFi.h>

const char ACCESS_POINT_SSID[] = "metar_map";
const char ACCESS_POINT_PASSWORD[] = "metarmappass";
const int ACCESS_POINT_CHANEL = 12;
const int MAX_ACCESS_POINT_CONNECTIONS = 1;

const IPAddress local_IP(192, 168, 0, 1);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

IPAddress startWiFiAccessPoint()
{
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ACCESS_POINT_SSID, ACCESS_POINT_PASSWORD, ACCESS_POINT_CHANEL, false, MAX_ACCESS_POINT_CONNECTIONS);

    return WiFi.localIP();
}
