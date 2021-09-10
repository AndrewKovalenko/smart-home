import os

CREDENTIALS_STORAGE = './storage/netwok-credentials'

def saveNetworkCredentials(ssid, password):
    credentialsFile = open(CREDENTIALS_STORAGE, 'w')
    credentialsFile.writelines([ssid, password])
    credentialsFile.close()

def readNetworkCredentials():
    credentialsFile = open(CREDENTIALS_STORAGE, 'r')
    [ssid, password] = credentialsFile.readlines()

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
    