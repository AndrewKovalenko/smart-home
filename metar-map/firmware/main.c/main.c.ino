#include <ESP8266WiFi.h>

const char *ssid = "metar_map";
const char *password = "metarmappass";
const int channel = 12;
const int maxConnections = 1;

IPAddress local_IP(192,168,0,2);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,254);

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password, channel, false, maxConnections);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
