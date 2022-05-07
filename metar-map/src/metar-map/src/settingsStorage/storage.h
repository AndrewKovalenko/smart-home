#include <EEPROM.h>
#include <Arduino.h>
#include "crc16.h"

#ifndef STORAGE_H
#define STORAGE_H

struct WiFiCredentials
{
    String ssid = "";
    String password = "";
    uint16_t crc;
};

#endif 

bool areCredentialsBlank(WiFiCredentials credentials);
void resetCredentialsStorage();
WiFiCredentials readWifiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);
