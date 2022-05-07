#include "boardManager.h"
#include "stationsToLedsMapping.h"

#define WIFI_RECONNECT_DELAY 500

BoardMode readMode()
{
    WiFiCredentials credentialsSaved = readWifiCredentials();

    return areCredentialsBlank(credentialsSaved) ? WiFiSetup : WeatherClient;
}

void startInWeatherClientMode()
{
}

void startInWiFiSetupMode()
{
}

void connectToWiFiNetwork(String baseUrl)
{
    WiFiCredentials savedCredentials = readWifiCredentials();

    const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));
    String weatherUrl = buildWeatherRetrievingUrl(
        baseUrl,
        metarStations,
        numberOfStations);

    WiFi.begin(savedCredentials.ssid, savedCredentials.password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(WIFI_RECONNECT_DELAY);
        Serial.print(".");
    }
}