import socket
import ure
from httperrors import RequestParsingError
from parsehelpers import parseBody

IP_KEY = 'ip_address'
PORT_KEY = 'port'
ENCODING = 'iso-8859-1'
REGULAR_STRING_ENCODING = 'utf-8'
URL = 'URL'
CONTENT_LENGTH = 'Content-Length'
HTTP_HEADER_SEPARATOR = ':'

REQUEST_PARSING_REFEXP_PATTERN = r"([A-Z]+)\s([\/\._\-?&=a-zA-Z0-9]+)\sHTTP\/1\.1"
CONTENT_LENGTH_PATTERN = r"(Content-Length)"

HTTP_METHOD_GROUP = 1
URL_GROUP = 2
CONTENT_LENGTH_GROUP = 1

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

    def __readContentLength(self, headersString):
        print('Headers passed: ', headersString)
        matchObject = self.__contentLengthRegexp.match(headersString)
        print('Match: ', matchObject)
        
        if matchObject is None:
            errorMessage = 'Content-Length header required'
            raise RequestParsingError(errorMessage)

        contentLength = matchObject.group(CONTENT_LENGTH_GROUP)
        print('Content length: ', contentLength)
        return int(contentLength.strip())

    def __readBody(self, contentLength, request):
        print('Content length: ', contentLength)
        bodyContentString = str(request.read(contentLength)) #.decode(REGULAR_STRING_ENCODING)

        print('Content: ', bodyContentString)
        return parseBody(bodyContentString)

    def __parseUrl(self, headersString):
        matchObject = self.__requestParsingRegexp.match(headersString)

        if matchObject is not None:
            method = matchObject.group(HTTP_METHOD_GROUP)
            path = matchObject.group(URL_GROUP)

            if (method is not None and path is not None):
                return (method, path)

        errorMessage = 'Unknown request format: ' + headersString
        raise RequestParsingError(errorMessage)

    def __readHeaders(self, request):
        headers = {}

        while True:
            line = request.readline()

            if not line or line == b'\r\n':
                break

            decodedLine = line.decode(REGULAR_STRING_ENCODING)

            if HTTP_HEADER_SEPARATOR not in decodedLine:
                headers[URL] = decodedLine
            else:
                print(decodedLine)
                [headerName, headerValue] = decodedLine.split(HTTP_HEADER_SEPARATOR, 1)
                headers[headerName.strip()] = headerValue.strip()

        return headers

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
            headers = self.__readHeaders(request)
            (method, url) = self.__parseUrl(headers[URL])
            print('Request:', method, url)

            if method == 'POST':
                contentLength = int(headers[CONTENT_LENGTH])
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
