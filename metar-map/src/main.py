# main.py
import importmodules
import accesspoint 
import appconfig

accessPoint = accesspoint.AccessPoint(appconfig.ACCESS_POINT_CREDENTIALS ,appconfig.ACCESS_POINT_NETWORK)
accessPoint.start()
