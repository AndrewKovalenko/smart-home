#include "accessPoint.h"

void startWiFiAccessPoint()
{
    Serial.println("Starting access point");
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ACCESS_POINT_SSID, ACCESS_POINT_PASSWORD);//, ACCESS_POINT_CHANEL, false, MAX_ACCESS_POINT_CONNECTIONS);
    Serial.println("AP started");
}
