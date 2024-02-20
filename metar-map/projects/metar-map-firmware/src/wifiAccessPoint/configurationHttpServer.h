#ifndef _CONFIG_UI_SERVER_
#define _CONFIG_UI_SERVER_

#include <ESP8266WebServer.h>
#include "../settingsStorage/storage.h"

ESP8266WebServer* startAccessPointConfigWebServer();

#endif