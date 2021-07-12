import socket

IP_KEY = 'ip_address'
PORT_KEY = 'port'

class NetworkSetupServer:
    def __init__(self, serverConfig):
        serverIp = serverConfig[IP_KEY] 
        serverPort = serverConfig[PORT_KEY] 

        serverAddress = socket.getaddrinfo(serverIp, serverPort)[0][-1] 
        httpServer = socket.socket()
        httpServer.bind(serverAddress)
        self.__httpServer = httpServer

        credentialsPageFile = open('html-ui/access-point.html', 'r')
        self.__credentialsHTML = credentialsPageFile.read()
        credentialsPageFile.close()

        self.__runServer = True

    def start(self):
        server = self.__httpServer

        server.listen(0)

        while self.__runServer:
            csock, caddr = server.accept()
            print("Connection from: " + str(caddr))
            req = csock.recv(1024)  # get the request, 1kB max
            print(req)
            # Look in the first line of the request for a move command
            # A move command should be e.g. 'http://server/move?a=90'
            filename = 'html-ui/access-point.html'
            f = open(filename, 'r')

            csock.sendall(str.encode("HTTP/1.0 200 OK\n",'iso-8859-1'))
            csock.sendall(str.encode('Content-Type: text/html\n', 'iso-8859-1'))
            csock.send(str.encode('\r\n'))
            # send data per line
            for l in f.readlines():
                print('Sent ', repr(l))
                csock.sendall(str.encode(""+l+"", 'iso-8859-1'))
                l = f.read(1024)
            f.close()

            csock.close()

