#ifndef _WEATHER_URL_BUILDER_
#define _WEATHER_URL_BUILDER_

#include <Arduino.h>
#include "weatherStation.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation stations[], uint8_t numberOfStations);

#endif