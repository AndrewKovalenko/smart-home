BODY_PROPERTIES_SEPARATOR = '&'
KEY_VALUE_SEPARATOR = '='


def parseBody(bodyString):
    result = {}
    properties = bodyString.split(BODY_PROPERTIES_SEPARATOR)

    for propertyString in properties:
        [key, value] = propertyString.split(KEY_VALUE_SEPARATOR)
        result[key] = value

    return result
