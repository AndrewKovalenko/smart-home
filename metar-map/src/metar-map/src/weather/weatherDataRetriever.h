#include <Arduino.h>
#import "weatherStation.h"

String buildWeatherRetrievingUrl(String baseUrl, WeatherStation metarStations[], uint8_t numberOfStations);