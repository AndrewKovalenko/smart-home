const int ONE_SECOND = 1000;

void startWiFiStation(WiFiCredentials credentials, int numberOfReconnects)
{
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);

    WiFi.begin(credentials.ssid, credentials.password);
    for (int i = 0; i < numberOfReconnects; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi");
            delay(ONE_SECOND);
        }
        else
        {
            return;
        }
    }
}