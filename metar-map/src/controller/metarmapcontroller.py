from modes import MetarMapControllerModes
import accesspoint 
import appconfig
from networksetupserver import NetworkSetupServer
import networkcredentials as networkCredentialsRepository


class MetarMapController:
    def __init__(self):
        self.__mode = MetarMapControllerModes.ACCESS_POINT

    def start(self):
        if self.__mode == MetarMapControllerModes.ACCESS_POINT:

            accessPoint = accesspoint.AccessPoint(appconfig.ACCESS_POINT_CREDENTIALS ,appconfig.ACCESS_POINT_NETWORK)
            accessPoint.start()

            apHttpServer = NetworkSetupServer({
                'ip_address': appconfig.ACCESS_POINT_NETWORK['loacl_ip'],
                'port': appconfig.HTTP_SERVER_PORT
            })
            print('Credentials saved: ', networkCredentialsRepository.areCredentialsSet())
            apHttpServer.startServer()


