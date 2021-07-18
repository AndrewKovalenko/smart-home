import socket
import ure
from httperrors import RequestParsingError

IP_KEY = 'ip_address'
PORT_KEY = 'port'
ENCODING = 'iso-8859-1'
DEFAULT_REQUEST_SIZE = 1024
REQUEST_PARSING_REFEXP_PATTERN = "^b'([A-Z]+)\s([\/\._\-?&=a-zA-Z0-9]+)\sHTTP\/1\.1$"
HTTP_METHOD_GROUP = 1
URL_GROUP = 2
REQUEST_SECTIONS_SEPARATOR = '\\r\\n'

class BaseHttpServer:
    ENCODING = 'iso-8859-1'

    def __init__(self, serverConfig):
        serverIp = serverConfig[IP_KEY]
        serverPort = serverConfig[PORT_KEY]

        serverAddress = socket.getaddrinfo(serverIp, serverPort)[0][-1] 
        httpServer = socket.socket()
        httpServer.bind(serverAddress)
        self.__httpServer = httpServer
        self.__requestParsingRegexp = ure.compile(REQUEST_PARSING_REFEXP_PATTERN)

    def __passeRequest(self, request):
        requestSections = repr(request).split(REQUEST_SECTIONS_SEPARATOR)
        requestTypeAndUrl = requestSections[0]
        matchObject = self.__requestParsingRegexp.match(requestTypeAndUrl)

        if matchObject is not None:
            method = matchObject.group(HTTP_METHOD_GROUP)
            path = matchObject.group(URL_GROUP)

            if(method is not None and path is not None):
                return (method, path)

        errorMessage = 'Unknown request format: ' + requestTypeAndUrl
        raise RequestParsingError(errorMessage)

    def __returnNotFound(self, connection):
        connection.sendall(str.encode("HTTP/1.0 404 Not Found\n", self.ENCODING))
        connection.sendall(str.encode('Content-Type: text/html\n', self.ENCODING))
        connection.close()
