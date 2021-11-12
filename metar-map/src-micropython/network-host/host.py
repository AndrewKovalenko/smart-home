import network as net
import time

class Host:
    def __init__(self, ssid, password, retries):
        host = net.WLAN(net.STA_IF)
        self.__host = host
        self.__ssid = ssid
        self.__password = password
        self.__retries = retries


    def connect(self):
        self.__host.active(True)

        if not self.__host.isconnected():
            self.__host.connect(self.__ssid, self.__password)

            attemptsMade = 1
            while attemptsMade <= self.__retries and not self.__host.isconnected():
                reconnectingInterval = 5 * attemptsMade
                print(
                    'Reconnecting to ', self.__ssid, ' with ', self.__password, ' at ', 
                    reconnectingInterval
                    )
                time.sleep(reconnectingInterval)
                attemptsMade = attemptsMade + 1

            return self.__host.isconnected()
