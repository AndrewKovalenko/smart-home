import os
import ubinascii

CREDENTIALS_STORAGE = './netwok-credentials'
CREDENTIALS_SEPARATOR = '@'
ENCODING = 'utf-8'

def saveNetworkCredentials(ssid, password):
    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'w')
        stringToSave = ssid + CREDENTIALS_SEPARATOR + password
        credentialsFile.write(ubinascii.b2a_base64(stringToSave))
    finally:
        credentialsFile.close()

def readNetworkCredentials():
    try:
        credentialsFile = open(CREDENTIALS_STORAGE, 'r', encoding=ENCODING)
        credentialsString = credentialsFile.read()
        print('Encoded credentials: ', credentialsString)
        decodedCredentials = ubinascii.a2b_base64(credentialsString)
        print('Decoded credentials: ', decodedCredentials)
    finally:
        credentialsFile.close()

    [ssid, password] = decodedCredentials.decode(ENCODING).split(CREDENTIALS_SEPARATOR, 1)

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
    