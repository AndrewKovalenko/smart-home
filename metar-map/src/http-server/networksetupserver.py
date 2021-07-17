import basehttpserver as base

IP_KEY = 'ip_address'
PORT_KEY = 'port'
ENCODING = 'iso-8859-1'

class NetworkSetupServer(base.BaseHttpServer):
    def __init__(self, serverConfig):
        super().__init__(serverConfig)

        credentialsPageFile = open('html-ui/access-point.html', 'r')

        self.__credentialsPageLines = []

        for line in credentialsPageFile.readlines():
            self.__credentialsPageLines.append(line)

        credentialsPageFile.close()

        self.__runServer = True

    def start(self):
        server = self.__httpServer

        server.listen(0)

        while self.__runServer:
            csock, caddr = server.accept()
            print("request from: " + str(caddr))
            req = csock.recv(1024)  # get the request, 1kB max
            (method, url) = super().__passeRequest(req)
            print('Parse results:',method, url)
            # Look in the first line of the request for a move command
            # A move command should be e.g. 'http://server/move?a=90'

            csock.sendall(str.encode("HTTP/1.0 200 OK\n", ENCODING))
            csock.sendall(str.encode('Content-Type: text/html\n', ENCODING))
            csock.send(str.encode('\r\n'))
            # send data per line
            for htmlLine in self.__credentialsPageLines:
                csock.sendall(str.encode(""+htmlLine+"", ENCODING))

            csock.close()

