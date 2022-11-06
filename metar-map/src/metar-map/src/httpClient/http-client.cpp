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
    if (weatherData["features"][i]["properties"] == NULL || weatherData["features"][i]["properties"]["id"] == NULL)
    {
      continue;
    }

    String stationName = weatherData["features"][i]["properties"]["id"];

    Serial.println("Reading station " + stationName);

    for (uint8_t j = 0; j < numberOfStations; j++)
    {
      if (metars[j].stationName == stationName)
      {
        const char *visibility = weatherData["features"][i]["properties"]["fltcat"];
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
        String result = https.getString();
        https.end();
        return result;
        Serial.println("[HTTPS] result: " + result);
      }
    }
    else
    {
      result = "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
    }

    https.end();
    delete client;
    return result;
  }
  else
  {
    delete client;
    return "[HTTPS] Unable to connect\n";
  }
}
