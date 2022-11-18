#include <ArduinoJson.h>
#include "http-client.h"

void parseResponse(String response, WeatherStation *metars, uint8_t numberOfStations)
{
  DynamicJsonDocument weatherData(MAX_SUPPORTED_REQUEST_SIZE);
  deserializeJson(weatherData, response);

  for (uint8_t i = 0; i < numberOfStations; i++)
  {
    String stationName = weatherData[i][STATION_PROPERTY_NAME];

    for (uint8_t j = 0; j < numberOfStations; j++)
    {
      if (metars[j].stationName == stationName)
      {
        const char *flightCategory = weatherData[i][FLIGHT_CATEGORY_PROPERTY_NAME];
        sprintf(metars[j].weather, "%s", flightCategory);
        break;
      }
    }
  }
}

String makeGetCall(String url)
{
  WiFiClient client;
  HTTPClient https;
  String result;

  if (https.begin(client, url))
  {
    int httpCode = https.GET();

    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        result = https.getString();
        https.end();
        return result;
      }
    }
    else
    {
      result = "";
    }

    https.end();
    return result;
  }
  else
  {
    return "[HTTPS] Unable to connect\n";
  }
}
