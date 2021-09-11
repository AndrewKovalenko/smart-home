import os

CREDENTIALS_STORAGE = './netwok-credentials'
CREDENTIALS_SEPARATOR = '@'

def saveNetworkCredentials(ssid, password):
    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'w')
        credentialsFile.write(ssid + CREDENTIALS_SEPARATOR + password)
    finally:
        credentialsFile.close()

def readNetworkCredentials():
    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'r', encoding='utf-8')
        credentialsString = credentialsFile.read()
    finally:
        credentialsFile.close()

    [ssid, password] = credentialsString.split(CREDENTIALS_SEPARATOR, 1)

    return {'ssid': ssid, 'password': password}

def areCredentialsSet():
    try:
        print('Storage status: ', os.stat(CREDENTIALS_STORAGE))
        return True

    except OSError:
        return False

def whipeOutCredentials():
    if areCredentialsSet():
        os.remove(CREDENTIALS_STORAGE)
    