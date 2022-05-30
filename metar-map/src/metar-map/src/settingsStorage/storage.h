#ifndef STORAGE_H
#define STORAGE_H
#include <EEPROM.h>
#include <Arduino.h>
#include "crc16.h"

#define READ_BUFFER_SIZE 512

struct WiFiCredentials
{
    char* ssid = "";
    char* password = "";
    uint16_t crc;
};


bool areCredentialsBlank(WiFiCredentials credentials);
void resetCredentialsStorage();
WiFiCredentials* readWifiCredentials();
void saveWiFiCredentials(WiFiCredentials credentials);

#endif 