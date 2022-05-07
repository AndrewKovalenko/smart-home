#include "boardManager.h"

BoardMode readMode() 
{ 
    WiFiCredentials credentialsSaved = readWifiCredentials();

    return areCredentialsBlank(credentialsSaved) ? WiFiSetup : WeatherClient;
}