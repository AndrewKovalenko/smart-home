
const char *SSID = "metar_map";
const char *PASSWORD = "metarmappass";
const int ACCESS_POINT_CHANEL = 12;
const int MAX_ACCESS_POINT_CONNECTIONS = 1;

const IPAddress local_IP(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 254);

void startWiFiAccessPoint()
{
    Serial.print("Setting AP (Access Point)…");

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(SSID, PASSWORD, ACCESS_POINT_CHANEL, false, MAX_ACCESS_POINT_CONNECTIONS);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    Serial.print("Local IP address: ");
    Serial.println(WiFi.localIP());
}
