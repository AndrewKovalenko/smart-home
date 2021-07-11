#include <ESP8266WebServer.h>
#include "index-page.h"

void wrapperForRootHandler(void *context)
{
    static_cast<HttpServer*>(context)->handleHttpRootCall();
}

class HttpServer
{
private:
    const char *ROOT_URL = "/";
    const char *RESPONSE_MIME_TYPE = "text/html";
    const int HTTP_SERVER_PORT = 80;
    ESP8266WebServer *builtInHttpServer;

public:
    HttpServer()
    {
        builtInHttpServer = new ESP8266WebServer(HTTP_SERVER_PORT);
    }
    ~HttpServer()
    {
        delete builtInHttpServer;
    }

    void handleHttpRootCall(){};
    void handleSavingWiFiCredentials(){};

    void StartServingWiFiCredentialsPage()
    {
        builtInHttpServer->on("/", HTTP_GET, wrapperForRootHandler, this);
        // this.httpServer.on("/connect", HTTP_POST, handleSavingWiFiCredentials);
        // this.httpServer.begin()
    };
};