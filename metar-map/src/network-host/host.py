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

            attemptsMade = 0
            while attemptsMade <= self.__retries and not self.__host.isconnected():
                time.sleep(5 * attemptsMade)

            return self.__host.isconnected()
