typedef struct WeatherStation
{
   String stationName;
   uint8_t ledNumber;
};

WeatherStation metarStations[25] = {
   {"KHQM", 1},
   {"KUIL", 6},
   {"KCLM", 9},
   {"CYYJ", 11},
   {"KFHR", 13},
   {"KORS", 14},
   {"KBLI", 15},
   {"KBVS", 17},
   {"KNUW", 18},
   {"KAWO", 20},
   {"K0S9", 22},
   {"KPAE", 24},
   {"KRNT", 26},
   {"KBFI", 27},
   {"KSEA", 28},
   {"KPWT", 30},
   {"KSHN", 32},
   {"KOLM", 33},
   {"KGRF", 34},
   {"KTIW", 35},
   {"KTCM", 36},
   {"KPLU", 37},
   {"KENL", 41},
   {"KEAT", 43},
   {"KS52", 48}
}; 