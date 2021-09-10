import basehttpserver as base


class NetworkSetupServer(base.BaseHttpServer):
    def __init__(self, serverConfig):
        super().__init__(serverConfig)

        credentialsPageFile = open('html-ui/access-point.html', 'r')

        self.__credentialsPageLines = []

        for line in credentialsPageFile.readlines():
            self.__credentialsPageLines.append(line)

        credentialsPageFile.close()

    def __homePage(self, _, respond):
        respond(self.__credentialsPageLines)

    def __saveWiFiCredentials(self, requestBody, respond):
        respond(self.__credentialsPageLines)

    __httpHandlers = {
        'GET': {
            '/': __homePage
        },

        'POST': {
            '/saveCredentials': __saveWiFiCredentials
        }
    }

    def startServer(self):
        super().start(self.__httpHandlers)
