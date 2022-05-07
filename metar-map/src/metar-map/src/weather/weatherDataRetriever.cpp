#include "weatherDataRetriever.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation metarStations[]) 
{
    String stationsQueryParameter = "";
    const uint8_t numberOfStations = (uint8_t)(sizeof(metarStations) / sizeof(metarStations[0]));

    for (uint8_t i=0; i<numberOfStations; i++)
    {
        stationsQueryParameter += metarStations[i].stationName;

        if(i != numberOfStations - 1)
        {
            stationsQueryParameter += "%20";
        }
    }

    return baseUrl + stationsQueryParameter;
}