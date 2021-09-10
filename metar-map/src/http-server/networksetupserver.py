import basehttpserver as base
from networkcredentials import saveNetworkCredentials
import boardapi

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
        saveNetworkCredentials(requestBody['network-ssid'], requestBody['wifi-password'])
        respond(self.__credentialsPageLines)

        boardapi.softReset()

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
