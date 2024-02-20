package internal

const testResponse = `
{
	"type": "FeatureCollection",
	"features": [
		{
			"type": "Feature",
			"properties": {
				"data": "METAR",
				"beg_time": "1668226832",
				"end_time": "1668234032",
				"wrap": "",
				"bbox": "-124.5700,46.9600,-120.1400,48.8000"
			}
		},
		{
			"type": "Feature",
			"id": "992202221",
			"properties": {
				"data": "METAR",
				"id": "KSEA",
				"site": "Seattle-Tacoma Intl",
				"prior": 0,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.6,
				"dewp": -0.6,
				"wspd": 6,
				"wdir": 20,
				"ceil": 180,
				"cover": "BKN",
				"cldCvg1": "SCT",
				"cldBas1": "120",
				"cldCvg2": "BKN",
				"cldBas2": "180",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.1,
				"slp": 1020.7,
				"rawOb": "KSEA 120553Z 02006KT 10SM SCT120 BKN180 06/M01 A3012 RMK AO2 SLP207 T00561006 10083 20050 53012"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.314,
					47.445
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199089",
			"properties": {
				"data": "METAR",
				"id": "KBLI",
				"site": "Bellingham Intl",
				"prior": 3,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 2.2,
				"dewp": -1.7,
				"wspd": 0,
				"wdir": 0,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.1,
				"slp": 1021.9,
				"rawOb": "KBLI 120553Z 00000KT 10SM OVC110 02/M02 A3015 RMK AO2 SLP219 T00221017 10061 20006 53005"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.541,
					48.799
				]
			}
		},
		{
			"type": "Feature",
			"id": "992202235",
			"properties": {
				"data": "METAR",
				"id": "KUIL",
				"site": "Quillayute State Arp",
				"prior": 3,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.0,
				"dewp": 1.7,
				"wspd": 3,
				"wdir": 60,
				"ceil": 80,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "80",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.4,
				"slp": 1019.5,
				"rawOb": "KUIL 120553Z AUTO 06003KT 10SM OVC080 05/02 A3010 RMK AO2 SLP195 T00500017 10061 20050 51014 $"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-124.558,
					47.937
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199103",
			"properties": {
				"data": "METAR",
				"id": "KHQM",
				"site": "Hoquiam/Bowerman Arp",
				"prior": 3,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 8.3,
				"dewp": 1.1,
				"wspd": 8,
				"wdir": 90,
				"ceil": 65,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "65",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.0,
				"slp": 1019.2,
				"rawOb": "KHQM 120553Z AUTO 09008KT 10SM OVC065 08/01 A3009 RMK AO2 SLP192 T00830011 10094 20078 53014"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.931,
					46.973
				]
			}
		},
		{
			"type": "Feature",
			"id": "992204899",
			"properties": {
				"data": "METAR",
				"id": "KEAT",
				"site": "Wenatchee/Pangborn M",
				"prior": 3,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": -1.7,
				"dewp": -4.4,
				"wspd": 4,
				"wdir": 280,
				"ceil": 100,
				"cover": "OVC",
				"cldCvg1": "FEW",
				"cldBas1": "65",
				"cldCvg2": "OVC",
				"cldBas2": "100",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1024.1,
				"slp": 1025.6,
				"rawOb": "KEAT 120555Z AUTO 28004KT 10SM FEW065 OVC100 M02/M04 A3024 RMK AO2 SLP256 T10171044 11011 21017 55000"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-120.201,
					47.397
				]
			}
		},
		{
			"type": "Feature",
			"id": "992207741",
			"properties": {
				"data": "METAR",
				"id": "KSMP",
				"site": "Stampede Pass",
				"prior": 4,
				"obsTime": "2022-11-12T05:56:00Z",
				"temp": -4.4,
				"dewp": -6.1,
				"wspd": 5,
				"wdir": 0,
				"cover": "FEW",
				"cldCvg1": "FEW",
				"cldBas1": "90",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1018.4,
				"slp": 1022.0,
				"rawOb": "KSMP 120556Z AUTO VRB05KT 10SM FEW090 M04/M06 A3007 RMK AO2 SLP220 T10441061 11039 21044 51004 $"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-121.338,
					47.276
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199529",
			"properties": {
				"data": "METAR",
				"id": "KPAE",
				"site": "Everett/Paine Fld",
				"prior": 4,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.0,
				"dewp": 0.0,
				"wspd": 5,
				"wdir": 360,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.4,
				"slp": 1020.6,
				"rawOb": "KPAE 120553Z AUTO 36005KT 10SM OVC110 05/00 A3013 RMK AO2 SLP206 T00500000 10061 20044 51010"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.283,
					47.923
				]
			}
		},
		{
			"type": "Feature",
			"id": "992202117",
			"properties": {
				"data": "METAR",
				"id": "KNUW",
				"site": "Whidbey Island(NAS)",
				"prior": 4,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.0,
				"dewp": -1.7,
				"wspd": 0,
				"wdir": 0,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1022.4,
				"slp": 1022.1,
				"rawOb": "KNUW 120553Z AUTO 00000KT 10SM OVC110 05/M02 A3019 RMK AO2 SLP221 T00501017 10067 20044 51009 VISNO $"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.664,
					48.355
				]
			}
		},
		{
			"type": "Feature",
			"id": "992207007",
			"properties": {
				"data": "METAR",
				"id": "KS52",
				"site": "Methow Valley State",
				"prior": 4,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": -5.4,
				"dewp": -6.9,
				"wspd": 0,
				"wdir": 0,
				"cover": "SCT",
				"cldCvg1": "SCT",
				"cldBas1": "75",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1024.8,
				"rawOb": "KS52 120555Z AUTO 00000KT 10SM SCT075 M05/M07 A3026 RMK AO2 T10541069 11049 21061"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-120.149,
					48.426
				]
			}
		},
		{
			"type": "Feature",
			"id": "992201829",
			"properties": {
				"data": "METAR",
				"id": "KOLM",
				"site": "Olympia Rgnl",
				"prior": 4,
				"obsTime": "2022-11-12T05:54:00Z",
				"temp": 5.6,
				"dewp": 1.1,
				"wspd": 0,
				"wdir": 0,
				"ceil": 50,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "50",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.1,
				"slp": 1020.0,
				"rawOb": "KOLM 120554Z 00000KT 10SM OVC050 06/01 A3012 RMK AO2 SLP200 T00560011 10078 20033 52016"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.905,
					46.977
				]
			}
		},
		{
			"type": "Feature",
			"id": "992213823",
			"properties": {
				"data": "METAR",
				"id": "CYYJ",
				"site": "Victoria Intl",
				"prior": 4,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 5.0,
				"dewp": 3.0,
				"wspd": 4,
				"wdir": 300,
				"ceil": 85,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "85",
				"visib": 20.00,
				"fltcat": "VFR",
				"altim": 1021.4,
				"slp": 1021.5,
				"rawOb": "CYYJ 120600Z 30004KT 20SM OVC085 05/03 A3016 RMK AC8 SLP215"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.433,
					48.642
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199183",
			"properties": {
				"data": "METAR",
				"id": "KCLM",
				"site": "Port Angeles Intl",
				"prior": 4,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.6,
				"dewp": 1.7,
				"wspd": 0,
				"wdir": 0,
				"ceil": 18,
				"cover": "OVC",
				"cldCvg1": "BKN",
				"cldBas1": "18",
				"cldCvg2": "OVC",
				"cldBas2": "26",
				"visib": 10.00,
				"fltcat": "MVFR",
				"altim": 1021.4,
				"slp": 1021.6,
				"rawOb": "KCLM 120553Z AUTO 00000KT 10SM BKN018 OVC026 06/02 A3016 RMK AO2 SLP216 T00560017 10061 20039 53007"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.507,
					48.122
				]
			}
		},
		{
			"type": "Feature",
			"id": "992202399",
			"properties": {
				"data": "METAR",
				"id": "KTCM",
				"site": "Tacoma/McChord AFB",
				"prior": 5,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": 4.3,
				"dewp": 1.2,
				"wspd": 0,
				"wdir": 0,
				"ceil": 170,
				"cover": "BKN",
				"cldCvg1": "FEW",
				"cldBas1": "110",
				"cldCvg2": "BKN",
				"cldBas2": "170",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.4,
				"slp": 1019.9,
				"rawOb": "KTCM 120555Z AUTO 00000KT 10SM FEW110 BKN170 04/01 A3010 RMK AO2 SLP199 T00430012 10083 20032 52013"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.475,
					47.149
				]
			}
		},
		{
			"type": "Feature",
			"id": "992204567",
			"properties": {
				"data": "METAR",
				"id": "KPWT",
				"site": "Bremerton Arpt",
				"prior": 5,
				"obsTime": "2022-11-12T05:56:00Z",
				"temp": 5.0,
				"dewp": 0.6,
				"wspd": 8,
				"wdir": 50,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.1,
				"slp": 1020.8,
				"rawOb": "KPWT 120556Z AUTO 05008KT 10SM OVC110 05/01 A3012 RMK AO2 SLP208 T00500006 10067 20044 53012"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.772,
					47.490
				]
			}
		},
		{
			"type": "Feature",
			"id": "992221629",
			"properties": {
				"data": "METAR",
				"id": "K0S9",
				"site": "Port Townsend/Jeffer",
				"prior": 5,
				"obsTime": "2022-11-12T06:15:00Z",
				"temp": 3.0,
				"dewp": 2.0,
				"wspd": 0,
				"wdir": 0,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.1,
				"rawOb": "K0S9 120615Z AUTO 00000KT 10SM OVC110 03/02 A3015 RMK AO2"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.812,
					48.055
				]
			}
		},
		{
			"type": "Feature",
			"id": "992221663",
			"properties": {
				"data": "METAR",
				"id": "KORS",
				"site": "Eastsound/Orcas Isla",
				"prior": 5,
				"obsTime": "2022-11-12T06:15:00Z",
				"temp": 7.0,
				"dewp": 3.0,
				"wspd": 4,
				"wdir": 360,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.4,
				"rawOb": "KORS 120615Z AUTO 36004KT 10SM OVC110 07/03 A3016 RMK AO2"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.909,
					48.708
				]
			}
		},
		{
			"type": "Feature",
			"id": "992202339",
			"properties": {
				"data": "METAR",
				"id": "KFHR",
				"site": "Friday Harbor Arpt",
				"prior": 5,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 6.7,
				"dewp": 2.2,
				"wspd": 8,
				"wdir": 10,
				"ceil": 110,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.4,
				"slp": 1021.2,
				"rawOb": "KFHR 120553Z AUTO 01008KT 10SM OVC110 07/02 A3016 RMK AO2 SLP212 T00670022 10067 20056 53006"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.026,
					48.520
				]
			}
		},
		{
			"type": "Feature",
			"id": "992204781",
			"properties": {
				"data": "METAR",
				"id": "KAWO",
				"site": "Arlington Muni",
				"prior": 5,
				"obsTime": "2022-11-12T05:56:00Z",
				"temp": 1.7,
				"dewp": -0.6,
				"wspd": 0,
				"wdir": 0,
				"ceil": 100,
				"cover": "BKN",
				"cldCvg1": "BKN",
				"cldBas1": "100",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.1,
				"slp": 1021.5,
				"rawOb": "KAWO 120556Z AUTO 00000KT 10SM BKN100 02/M01 A3015 RMK AO2 SLP215 T00171006 10067 20011 53012 FZRANO"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.159,
					48.158
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199201",
			"properties": {
				"data": "METAR",
				"id": "KSHN",
				"site": "Shelton/Sanderson Fl",
				"prior": 5,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.6,
				"dewp": 0.6,
				"wspd": 4,
				"wdir": 10,
				"ceil": 70,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "70",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.4,
				"slp": 1019.6,
				"rawOb": "KSHN 120553Z AUTO 01004KT 10SM OVC070 06/01 A3010 RMK AO2 SLP196 T00560006 10078 20039 53013"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.141,
					47.238
				]
			}
		},
		{
			"type": "Feature",
			"id": "992215065",
			"properties": {
				"data": "METAR",
				"id": "CWSP",
				"site": "Sheringham(AUTO)",
				"prior": 5,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 5.6,
				"dewp": 0.8,
				"wspd": 5,
				"wdir": 90,
				"slp": 1021.1,
				"rawOb": "CWSP 120600Z AUTO 09005KT 06/01 RMK AO1 SLP211 T00560008 52011"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.921,
					48.377
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199159",
			"properties": {
				"data": "METAR",
				"id": "KELN",
				"site": "Ellensburg/Bowers Fl",
				"prior": 5,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 0.0,
				"dewp": -3.9,
				"wspd": 3,
				"wdir": 350,
				"ceil": 110,
				"cover": "BKN",
				"cldCvg1": "BKN",
				"cldBas1": "110",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1022.4,
				"slp": 1024.3,
				"rawOb": "KELN 120553Z AUTO 35003KT 10SM BKN110 00/M04 A3019 RMK AO2 SLP243 T00001039 10017 20000 53001"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-120.531,
					47.034
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199179",
			"properties": {
				"data": "METAR",
				"id": "KBFI",
				"site": "Seattle/Boeing Fld",
				"prior": 6,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 5.6,
				"dewp": 1.7,
				"wspd": 0,
				"wdir": 0,
				"cover": "CLR",
				"cldCvg1": "CLR",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.4,
				"slp": 1020.2,
				"rawOb": "KBFI 120553Z 00000KT 10SM CLR 06/02 A3013 RMK AO2 SLP202 T00560017 10083 20050 53012 $"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.315,
					47.546
				]
			}
		},
		{
			"type": "Feature",
			"id": "992215037",
			"properties": {
				"data": "METAR",
				"id": "CWQK",
				"site": "Race Rocks(AUTO)",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"wspd": 10,
				"wdir": 20,
				"rawOb": "CWQK 120600Z AUTO 02010KT RMK AO1 PK WND 01018/0514 53009"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.531,
					48.298
				]
			}
		},
		{
			"type": "Feature",
			"id": "992204507",
			"properties": {
				"data": "METAR",
				"id": "KPLU",
				"site": "Tacoma/Pierce Cnty",
				"prior": 6,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": 3.0,
				"dewp": 3.0,
				"wspd": 0,
				"wdir": 0,
				"ceil": 120,
				"cover": "BKN",
				"cldCvg1": "SCT",
				"cldBas1": "80",
				"cldCvg2": "BKN",
				"cldBas2": "120",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.7,
				"rawOb": "KPLU 120555Z AUTO 00000KT 10SM SCT080 BKN120 03/03 A3011 RMK AO2"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.286,
					47.101
				]
			}
		},
		{
			"type": "Feature",
			"id": "992214987",
			"properties": {
				"data": "METAR",
				"id": "CWKH",
				"site": "Malahat (AUTO8)",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 2.9,
				"dewp": -0.3,
				"slp": 1020.2,
				"rawOb": "CWKH 120600Z AUTO 03/M00 RMK AO1 SLP202 T00291003 51007"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.542,
					48.568
				]
			}
		},
		{
			"type": "Feature",
			"id": "992167281",
			"properties": {
				"data": "METAR",
				"id": "CYWH",
				"site": "Victoria Harbour Arp",
				"prior": 6,
				"obsTime": "2022-11-12T05:00:00Z",
				"temp": 6.0,
				"dewp": 3.0,
				"wspd": 4,
				"wdir": 350,
				"ceil": 50,
				"cover": "OVC",
				"cldCvg1": "FEW",
				"cldBas1": "20",
				"cldCvg2": "BKN",
				"cldBas2": "50",
				"cldCvg3": "OVC",
				"cldBas3": "70",
				"visib": 15.00,
				"fltcat": "VFR",
				"altim": 1021.1,
				"slp": 1021.2,
				"rawOb": "CYWH 120500Z 35004KT 320V030 15SM FEW020 BKN050 OVC070 06/03 A3015 RMK CU1SC4AC2 LAST STFD OBS/NEXT 121400Z SLP212"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.387,
					48.423
				]
			}
		},
		{
			"type": "Feature",
			"id": "992221815",
			"properties": {
				"data": "METAR",
				"id": "KBVS",
				"site": "Burlington/Skagit Rg",
				"prior": 6,
				"obsTime": "2022-11-12T06:15:00Z",
				"temp": 3.0,
				"dewp": -1.0,
				"wspd": 5,
				"wdir": 310,
				"ceil": 100,
				"cover": "BKN",
				"cldCvg1": "BKN",
				"cldBas1": "100",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1021.4,
				"rawOb": "KBVS 120615Z AUTO 31005KT 10SM BKN100 03/M01 A3016 RMK A01"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.419,
					48.470
				]
			}
		},
		{
			"type": "Feature",
			"id": "992201777",
			"properties": {
				"data": "METAR",
				"id": "KTIW",
				"site": "Tacoma Narrows Arpt",
				"prior": 6,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 6.7,
				"dewp": 2.2,
				"wspd": 6,
				"wdir": 20,
				"cover": "SCT",
				"cldCvg1": "SCT",
				"cldBas1": "120",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.7,
				"slp": 1019.8,
				"rawOb": "KTIW 120553Z AUTO 02006KT 10SM SCT120 07/02 A3011 RMK AO2 SLP198 T00670022 10083 20067 53011"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.576,
					47.267
				]
			}
		},
		{
			"type": "Feature",
			"id": "992214995",
			"properties": {
				"data": "METAR",
				"id": "CWLM",
				"site": "Victoria(AUTO)",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 5.1,
				"dewp": 2.6,
				"wspd": 8,
				"wdir": 10,
				"slp": 1021.0,
				"rawOb": "CWLM 120600Z AUTO 01008KT 05/03 RMK AO1 SLP210 T00510026 51011"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.325,
					48.413
				]
			}
		},
		{
			"type": "Feature",
			"id": "992214809",
			"properties": {
				"data": "METAR",
				"id": "CWYJ",
				"site": "Victoria University",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 5.4,
				"dewp": 2.9,
				"wspd": 4,
				"wdir": 360,
				"slp": 1021.3,
				"rawOb": "CWYJ 120600Z AUTO 36004KT 05/03 RMK AO1 SLP213 T00540029 52009"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.305,
					48.457
				]
			}
		},
		{
			"type": "Feature",
			"id": "992214817",
			"properties": {
				"data": "METAR",
				"id": "CWZO",
				"site": "Kelp Reefs(NAV)",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"wspd": 15,
				"wdir": 10,
				"rawOb": "CWZO 120600Z AUTO 01015KT RMK AO1 PK WND 02017/0520"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.265,
					48.568
				]
			}
		},
		{
			"type": "Feature",
			"id": "992216935",
			"properties": {
				"data": "METAR",
				"id": "CWEZ",
				"site": "Saturna Isl(MARS)",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 6.3,
				"dewp": 3.5,
				"wspd": 3,
				"wdir": 340,
				"slp": 1020.9,
				"rawOb": "CWEZ 120600Z AUTO 34003KT 06/04 RMK AO1 SLP209 T00630035 53007"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.046,
					48.783
				]
			}
		},
		{
			"type": "Feature",
			"id": "992214963",
			"properties": {
				"data": "METAR",
				"id": "CWPF",
				"site": "Esquimalt Harbor",
				"prior": 6,
				"obsTime": "2022-11-12T06:00:00Z",
				"temp": 5.9,
				"dewp": 2.0,
				"wspd": 8,
				"wdir": 10,
				"slp": 1021.1,
				"rawOb": "CWPF 120600Z AUTO 01008KT 06/02 RMK AO1 SLP211 T00590020 52009"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.439,
					48.432
				]
			}
		},
		{
			"type": "Feature",
			"id": "992202363",
			"properties": {
				"data": "METAR",
				"id": "KGRF",
				"site": "Fort Lewis/Gray(AAF)",
				"prior": 6,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": 3.3,
				"dewp": 1.0,
				"wspd": 0,
				"wdir": 0,
				"ceil": 180,
				"cover": "BKN",
				"cldCvg1": "FEW",
				"cldBas1": "100",
				"cldCvg2": "BKN",
				"cldBas2": "180",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1019.0,
				"slp": 1019.6,
				"rawOb": "KGRF 120555Z AUTO 00000KT 10SM FEW100 BKN180 03/01 A3009 RMK AO2 SLP196 T00330010 10077 20033 52014 $"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.580,
					47.079
				]
			}
		},
		{
			"type": "Feature",
			"id": "992199499",
			"properties": {
				"data": "METAR",
				"id": "KRNT",
				"site": "Renton Muni",
				"prior": 7,
				"obsTime": "2022-11-12T05:53:00Z",
				"temp": 6.1,
				"dewp": 1.7,
				"wspd": 0,
				"wdir": 0,
				"cover": "CLR",
				"cldCvg1": "CLR",
				"visib": 10.00,
				"fltcat": "VFR",
				"altim": 1020.1,
				"slp": 1020.6,
				"rawOb": "KRNT 120553Z AUTO 00000KT 10SM CLR 06/02 A3012 RMK AO2 SLP206 T00610017 10094 20061 53014"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-122.214,
					47.495
				]
			}
		},
		{
			"type": "Feature",
			"id": "992209805",
			"properties": {
				"data": "METAR",
				"id": "KNOW",
				"site": "Port Angeles(CGAS)",
				"prior": 7,
				"obsTime": "2022-11-12T05:55:00Z",
				"temp": 6.0,
				"dewp": 4.0,
				"wspd": 4,
				"wdir": 160,
				"ceil": 14,
				"cover": "OVC",
				"cldCvg1": "OVC",
				"cldBas1": "14",
				"visib": 10.00,
				"fltcat": "MVFR",
				"altim": 1021.4,
				"rawOb": "KNOW 120555Z AUTO 16004KT 10SM OVC014 06/04 A3016 RMK AO2 T00600040 10063 20052"
			},
			"geometry": {
				"type": "Point",
				"coordinates": [
					-123.414,
					48.141
				]
			}
		}
	]
}
`
