import network as net
import accesspointconfig


class AccessPoint:
    def __init__(self, networkCredentials, networkConfiguration):
        accessPoint = net.WLAN(net.AP_IF)
        accessPoint.config(essid=networkCredentials['ssid'],
                           password=networkCredentials['password']
        )
        accessPoint.ifconfig(
            (networkConfiguration['loacl_ip'],
             networkConfiguration['subnet_mask'],
             networkConfiguration['gateway'],
             accesspointconfig.DEFAULT_DNS)
        )

        self.__accessPoint = accessPoint

    def start(self):
        self.__accessPoint.active(True)

    def stop(self):
        self.__accessPoint.active(False)
