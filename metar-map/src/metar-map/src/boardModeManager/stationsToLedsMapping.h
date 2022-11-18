#ifndef _STATIONS_TO_LED_
#define _STATIONS_TO_LED_

#include "../weather/weatherStation.h"

#define NUMBER_OF_STATIONS 26

WeatherStation metarStations[NUMBER_OF_STATIONS] = {
    {"KEAT", 0, ""},
    // {"KELN", 2, ""},
    {"KYKM", 2, ""},
    {"KSMP", 4, ""},
    {"KPLU", 6, ""},
    {"KRNT", 8, ""},
    {"KBFI", 9, ""},
    {"KSEA", 10, ""},
    {"KTIW", 11, ""},
    {"KTCM", 12, ""},
    {"KGRF", 13, ""},
    {"KPWT", 15, ""},
    {"KOLM", 17, ""},
    {"KSHN", 18, ""},
    {"KHQM", 20, ""},
    {"KUIL", 24, ""},
    {"KCLM", 27, ""},
    {"CYYJ", 29, ""},
    {"KFHR", 30, ""},
    {"KORS", 31, ""},
    {"KBLI", 32, ""},
    {"KBVS", 34, ""},
    {"KNUW", 35, ""},
    {"K0S9", 36, ""},
    {"KPAE", 38, ""},
    {"KAWO", 39, ""},
    {"KS52", 44, ""}};

#endif