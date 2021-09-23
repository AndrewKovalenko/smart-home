import os
from parse import unquote

CREDENTIALS_STORAGE = './netwok-credentials'
CREDENTIALS_SEPARATOR = '@'
ENCODING = 'utf-8'

def saveNetworkCredentials(ssid, password):
    print('Credentials recieved: ', ssid, ' ', password)
    ssid = unquote(ssid)
    password = unquote(password)
    print('Credentials after decoding: ', ssid, ' ', password)

    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'w', encoding=ENCODING)
        stringToSave = ssid + CREDENTIALS_SEPARATOR + password
        credentialsFile.write(stringToSave)
    finally:
        credentialsFile.close()

        print('Saved credentials: ', stringToSave)

def readNetworkCredentials():
    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'r', encoding=ENCODING)
        credentialsString = credentialsFile.read()
        print('Credentials read from storage: ', credentialsString)
    except OSError:
        return None
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
    