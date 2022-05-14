#include "accessPoint.h"

void startWiFiAccessPoint()
{
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ACCESS_POINT_SSID, ACCESS_POINT_PASSWORD, ACCESS_POINT_CHANEL, false, MAX_ACCESS_POINT_CONNECTIONS);
}
