#include "weatherDataRetriever.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation stations[], uint8_t numberOfStations) 
{
    String stationsQueryParameter = "";
    // const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(stations[0]));
    Serial.println("Numbrer of stations: " + String(numberOfStations));

    for (uint8_t i=0; i<numberOfStations; i++)
    {
        stationsQueryParameter += stations[i].stationName;

        if(i != numberOfStations - 1)
        {
            stationsQueryParameter += "%20";
        }
    }

    Serial.println("Query parans: " + stationsQueryParameter);

    return baseUrl + stationsQueryParameter;
}