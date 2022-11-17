#include <ArduinoJson.h>
#include "http-client.h"

void parseResponse(String response, WeatherStation *metars, uint8_t numberOfStations)
{
  Serial.println("Response is:");
  Serial.println(response);
  DynamicJsonDocument weatherData(MAX_SUPPORTED_REQUEST_SIZE);
  deserializeJson(weatherData, response);

  Serial.println("Data deserialized");
  for (uint8_t i = 0; i < numberOfStations; i++)
  {
    String stationName = weatherData[i][STATION_PROPERTY_NAME];

    Serial.println("Reading station " + stationName);

    for (uint8_t j = 0; j < numberOfStations; j++)
    {
      if (metars[j].stationName == stationName)
      {
        const char *flightCategory = weatherData[i][FLIGHT_CATEGORY_PROPERTY_NAME];
        Serial.println(flightCategory);
        sprintf(metars[j].weather, "%s", flightCategory);
        break;
      }
    }
  }
}

String makeGetCall(String url)
{
  // std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  // client->setInsecure();

  WiFiClient client;
  HTTPClient https;
  String result;

  // if (https.begin(*client, url))
  if (https.begin(client, url))
  {
    Serial.println("Url: " + url);

    Serial.print("[HTTPS] GET...\n");
    int httpCode = https.GET();

    if (httpCode > 0)
    {
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        result = https.getString();
        https.end();
        return result;
        Serial.println("[HTTPS] result: " + result);
      }
    }
    else
    {
      result = "";
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
    return result;
  }
  else
  {
    return "[HTTPS] Unable to connect\n";
  }
}
