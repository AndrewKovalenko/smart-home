import socket

IP_KEY = 'ip_address'
PORT_KEY = 'port'
ENCODING = 'iso-8859-1'

class NetworkSetupServer:
    def __init__(self, serverConfig):
        serverIp = serverConfig[IP_KEY]
        serverPort = serverConfig[PORT_KEY]

        serverAddress = socket.getaddrinfo(serverIp, serverPort)[0][-1] 
        httpServer = socket.socket()
        httpServer.bind(serverAddress)
        self.__httpServer = httpServer

        credentialsPageFile = open('html-ui/access-point.html', 'r')
        self.__credentialsPageLines = []

        for line in credentialsPageFile.readlines():
            self.__credentialsPageLines.append(line)

        credentialsPageFile.close()
        self.__runServer = True
        print(len(self.__credentialsPageLines))

    def start(self):
        server = self.__httpServer

        server.listen(0)

        while self.__runServer:
            csock, caddr = server.accept()
            print("Connection from: " + str(caddr))
            req = csock.recv(1024)  # get the request, 1kB max
            print(req, "\r\n")
            # Look in the first line of the request for a move command
            # A move command should be e.g. 'http://server/move?a=90'

            csock.sendall(str.encode("HTTP/1.0 200 OK\n", ENCODING))
            csock.sendall(str.encode('Content-Type: text/html\n', ENCODING))
            csock.send(str.encode('\r\n'))
            # send data per line
            print('Total lines:', len(self.__credentialsPageLines))
            for htmlLine in self.__credentialsPageLines:
                csock.sendall(str.encode(""+htmlLine+"", ENCODING))
                # print(htmlLine)

            csock.close()

