#import "stationsToLed.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation metarStations[], uint8_t numberOfStations) 
{
    String stationsQueryParameter = "";
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