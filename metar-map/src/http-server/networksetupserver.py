import basehttpserver as base

IP_KEY = 'ip_address'
PORT_KEY = 'port'
REQUEST_FRAME_SIZE = 1024

class NetworkSetupServer(base.BaseHttpServer):
    def __init__(self, serverConfig):
        super().__init__(serverConfig)

        credentialsPageFile = open('html-ui/access-point.html', 'r')

        self.__credentialsPageLines = []

        for line in credentialsPageFile.readlines():
            self.__credentialsPageLines.append(line)

        credentialsPageFile.close()

        self.__runServer = True

    def __getRespond(self, connection):
        def respond(response):
            connection.sendall(str.encode("HTTP/1.0 200 OK\n", self.ENCODING))
            connection.sendall(str.encode('Content-Type: text/html\n', self.ENCODING))
            connection.send(str.encode('\r\n'))

            if isinstance(response, list):
                for stringLine in response:
                    connection.sendall(str.encode(""+stringLine+"", self.ENCODING))
            elif isinstance(response, str):
                connection.sendall(str.encode(""+response+"", self.ENCODING))
            else:
                connection.close()
                raise TypeError('Unsuported response type')

            connection.close()

        return respond

    def start(self):
        server = self.__httpServer

        server.listen(0)

        while self.__runServer:
            request, caddr = server.accept()
            print("request from: " + str(caddr))
            req = request.recv(REQUEST_FRAME_SIZE)  # get the request, 1kB max
            (method, url) = super().__passeRequest(req)
            print('Parse results:',method, url)

            try:
                if method in self.__httpHandlers and \
                    url in self.__httpHandlers[method]:
                    respondFunction = self.__getRespond(request)
                    print(respondFunction)
                    handlerFunction = self.__httpHandlers[method][url]
                    handlerFunction(self, respondFunction)
                else:
                    super().__returnNotFound(request)

            finally:
                request.close()
    
    def __homePage(self, respond):
        print(self, respond)
        respond(self.__credentialsPageLines)

    __httpHandlers = {
        'GET': {
            '/': __homePage
        }
    }
