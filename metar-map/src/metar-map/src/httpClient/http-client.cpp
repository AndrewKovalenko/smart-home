#include <ArduinoJson.h>
#include "http-client.h"

void parseResponse(String response, WeatherStation (&metars)[], uint8_t numberOfStations)
{
  Serial.println("Response is:");
  Serial.println(response);
  DynamicJsonDocument weatherData(30720);
  deserializeJson(weatherData, response);

  Serial.println("Data deserialized");
  for (uint8_t i = 0; i < numberOfStations; i++)
  {
    String stationName = weatherData[i][STATION_NAME];

    Serial.println("Reading station " + stationName);

    for (uint8_t j = 0; j < numberOfStations; j++)
    {
      if (metars[j].stationName == stationName)
      {
        const char *visibility = weatherData[i]["visib"];
        Serial.println(visibility);
        metars[j].weather = "VFR";
        break;
      }
    }
  }
}

String makeGetCall(String url)
{
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  String result;

  client->setInsecure();

  HTTPClient https;

  if (https.begin(*client, url))
  { // HTTPS

    Serial.print("[HTTPS] GET...\n");
    int httpCode = https.GET();

    if (httpCode > 0)
    {
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        result = https.getString();
        Serial.println("[HTTPS] result: " + result);
      }
    }
    else
    {
      result = "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }

    https.end();
    return result;
  }
  else
  {
    return "[HTTPS] Unable to connect\n";
  }
}
