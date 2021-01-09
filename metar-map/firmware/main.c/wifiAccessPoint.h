
const char *ssid = "metar_map";
const char *password = "metarmappass";
const int channel = 12;
const int maxConnections = 1;

const IPAddress local_IP(192, 168, 0, 2);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 254);

void startWiFiAccessPoint()
{
    Serial.print("Setting AP (Access Point)…");

    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password, channel, false, maxConnections);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    Serial.println(WiFi.localIP());
}
