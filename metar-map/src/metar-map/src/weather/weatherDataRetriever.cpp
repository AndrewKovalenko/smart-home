#include "weatherDataRetriever.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation stations[], uint8_t numberOfStations) 
{
    String stationsQueryParameter = "";

    for (uint8_t i=0; i<numberOfStations; i++)
    {
        stationsQueryParameter += stations[i].stationName;

        if(i != numberOfStations - 1)
        {
            stationsQueryParameter += "%20";
        }
    }

    return baseUrl + stationsQueryParameter;
}