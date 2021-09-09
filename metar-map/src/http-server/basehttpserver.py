import socket
import ure
from httperrors import RequestParsingError
from parsehelpers import parseBody

IP_KEY = 'ip_address'
PORT_KEY = 'port'
ENCODING = 'iso-8859-1'
REGULAR_STRING_ENCODING = 'utf-8'
DEFAULT_REQUEST_SIZE = 1024

REQUEST_PARSING_REFEXP_PATTERN = r"^b'([A-Z]+)\s([\/\._\-?&=a-zA-Z0-9]+)\sHTTP\/1\.1$"
CONTENT_LENGTH_PATTERN = r".+?Content-Length:\s(\d+)"

HTTP_METHOD_GROUP = 1
URL_GROUP = 2
CONTENT_LENGTH_GROUP = 1

REQUEST_SECTIONS_SEPARATOR = '\\r\\n'
REQUEST_FRAME_SIZE = 1024
IP_KEY = 'ip_address'
PORT_KEY = 'port'


class BaseHttpServer:
    ENCODING = 'iso-8859-1'

    def __init__(self, serverConfig):
        serverIp = serverConfig[IP_KEY]
        serverPort = serverConfig[PORT_KEY]

        serverAddress = socket.getaddrinfo(serverIp, serverPort)[0][-1]
        httpServer = socket.socket()
        httpServer.bind(serverAddress)
        self.__httpServer = httpServer
        self.__requestParsingRegexp = ure.compile(
            REQUEST_PARSING_REFEXP_PATTERN)
        self.__contentLengthRegexp = ure.compile(CONTENT_LENGTH_PATTERN)
        self.__runServer = True

    def __readContentLength(self, headers):
        requestText = repr(headers)
        print('Headers: ', requestText)
        matchObject = self.__contentLengthRegexp.match(requestText)
        contentLength = matchObject.group(CONTENT_LENGTH_GROUP)
        return int(contentLength.strip())

    def __readBody(self, contentLength, request):
        print('Content length: ', contentLength)
        bodyContentString = request.read(contentLength).decode(REGULAR_STRING_ENCODING)

        print('Content: ', bodyContentString)
        return parseBody(bodyContentString)

    def __parseUrl(self, request):
        requestSections = repr(request).split(REQUEST_SECTIONS_SEPARATOR)
        requestTypeAndUrl = requestSections[0]
        matchObject = self.__requestParsingRegexp.match(requestTypeAndUrl)

        if matchObject is not None:
            method = matchObject.group(HTTP_METHOD_GROUP)
            path = matchObject.group(URL_GROUP)

            if (method is not None and path is not None):
                return (method, path)

        errorMessage = 'Unknown request format: ' + requestTypeAndUrl
        raise RequestParsingError(errorMessage)

    def __getRespond(self, connection):
        def respond(response):
            connection.sendall(str.encode("HTTP/1.0 200 OK\n", self.ENCODING))
            connection.sendall(
                str.encode('Content-Type: text/html\n', self.ENCODING))
            connection.send(str.encode('\r\n'))

            if isinstance(response, list):
                for stringLine in response:
                    connection.sendall(
                        str.encode("" + stringLine + "", self.ENCODING))
            elif isinstance(response, str):
                connection.sendall(
                    str.encode("" + response + "", self.ENCODING))
            else:
                connection.close()
                raise TypeError('Unsuported response type')

            connection.close()

        return respond

    def __returnNotFound(self, connection):
        connection.sendall(
            str.encode("HTTP/1.0 404 Not Found\n", self.ENCODING))
        connection.sendall(
            str.encode('Content-Type: text/html\n', self.ENCODING))
        connection.close()

    def start(self, httpHandlers):
        server = self.__httpServer

        server.listen(0)

        while self.__runServer:
            request, _ = server.accept()
            headers = request.recv(REQUEST_FRAME_SIZE)
            (method, url) = self.__parseUrl(headers)
            print('Request:', method, url)

            if method == 'POST':
                contentLength = self.__readContentLength(headers)
                body = self.__readBody(contentLength, request)
                print(body)

            try:
                if method in httpHandlers and \
                    url in httpHandlers[method]:
                    respondFunction = self.__getRespond(request)
                    handlerFunction = httpHandlers[method][url]
                    handlerFunction(self, respondFunction)
                else:
                    self.__returnNotFound(request)

            finally:
                request.close()
