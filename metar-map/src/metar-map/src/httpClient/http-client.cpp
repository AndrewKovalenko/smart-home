#include <ArduinoJson.h>
#include "http-client.h"
#include "../weather/weatherConditions.h"

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

        if (flightCategory[0] == 'V')
        {
          metars[j].weather = VFR;
          break;
        }

        if (flightCategory[0] == 'M')
        {
          metars[j].weather = MVFR;
          break;
        }

        if (flightCategory[0] == 'I')
        {
          metars[j].weather = IFR;
          break;
        }

        if (flightCategory[0] == 'L')
        {
          metars[j].weather = LIFR;
          break;
        }

        metars[j].weather = UNDEFINED;
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
