from modes import MetarMapControllerModes
import accesspoint 
import appconfig
from networksetupserver import NetworkSetupServer
import networkcredentials as networkCredentialsRepository
from host import Host
import boardapi


class MetarMapController:
    def __init__(self):
        if networkCredentialsRepository.areCredentialsSet():
            self.__mode =  MetarMapControllerModes.MAP

        else:
            self.__mode = MetarMapControllerModes.ACCESS_POINT

    def startAccessPoint(self):
        accessPoint = accesspoint.AccessPoint(appconfig.ACCESS_POINT_CREDENTIALS ,appconfig.ACCESS_POINT_NETWORK)
        accessPoint.start()

        apHttpServer = NetworkSetupServer({
            'ip_address': appconfig.ACCESS_POINT_NETWORK['loacl_ip'],
            'port': appconfig.HTTP_SERVER_PORT
        })

        apHttpServer.startServer()

    def startMap():
        networkCredentials = networkCredentialsRepository.readNetworkCredentials()
        host = Host(
            networkCredentials['ssid'],
            networkCredentials['password'],
            appconfig.CONNECTION_RETRIES
        )

        if not host.connect():
            networkCredentialsRepository.whipeOutCredentials()
            boardapi.softReset()

    def start(self):
        if self.__mode == MetarMapControllerModes.ACCESS_POINT:
            self.startAccessPoint()
        else:
            self.startMap()


