#include <EEPROM.h>
#include <Arduino.h>
#include "crc16.h"

struct WiFiCredentials
{
    String ssid = "";
    String password = "";
    uint16_t crc;
};