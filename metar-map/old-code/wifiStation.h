const uint16 WIFI_CONNECTION_SUCCESSFULL = 0;
const uint16 WIFI_CONNECTION_FAILED = 1;

uint16 startWiFiClient(WiFiCredentials credentials, int numberOfReconnects)
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
            return WIFI_CONNECTION_SUCCESSFULL;
        }
    }

    return WIFI_CONNECTION_FAILED;
}