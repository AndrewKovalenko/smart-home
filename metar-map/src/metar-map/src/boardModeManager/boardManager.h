#include "../settingsStorage/storage.h"

enum BoardMode {
  WeatherClient, 
  WiFiSetup
};

BoardMode readMode();