use serde::Deserialize;

#[derive(Deserialize, Debug)]
#[serde(untagged)]
pub(crate) enum WeatherServerVisibility {
    Unrestricted(String),
    Specific(f32),
}

#[derive(Deserialize, Debug)]
pub(crate) struct CloudLayer {
    #[serde(rename = "cover")]
    pub coverage_type: String,

    #[serde(rename = "base")]
    pub bases_altitude: u16,
}

#[derive(Deserialize, Debug)]
pub(crate) struct WeatherServerRecord {
    #[serde(rename = "icaoId")]
    pub station_id: String,

    #[serde(rename = "visib")]
    pub visibility: Option<WeatherServerVisibility>,

    #[serde(rename = "clouds")]
    pub sky_coverage: Vec<CloudLayer>,
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json;

    const COMPLETE_DATA_SAMPLE: &str = r#"
    {
    "metar_id": 501717771,
    "icaoId": "KEAT",
    "receiptTime": "2024-02-22 14:16:27",
    "obsTime": 1708611180,
    "reportTime": "2024-02-22 14:13:00",
    "temp": 1.7,
    "dewp": 0.6,
    "wdir": 330,
    "wspd": 5,
    "wgst": null,
    "visib": "10+",
    "altim": 1024.8,
    "slp": null,
    "qcField": 6,
    "wxString": null,
    "presTend": null,
    "maxT": null,
    "minT": null,
    "maxT24": null,
    "minT24": null,
    "precip": null,
    "pcp3hr": null,
    "pcp6hr": null,
    "pcp24hr": null,
    "snow": null,
    "vertVis": null,
    "metarType": "SPECI",
    "rawOb": "KEAT 221413Z AUTO 33005KT 10SM BKN007 02\/01 A3026 RMK AO2 T00170006",
    "mostRecent": 1,
    "lat": 47.3975,
    "lon": -120.201,
    "elev": 375,
    "prior": 3,
    "name": "Wenatchee\/Pangborn Mem, WA, US",
    "clouds": [
      {
        "cover": "BKN",
        "base": 700
      }
    ]
  }
    "#;

    #[test]
    fn successful_parse_weather_record() {
        let weather_record_parsing_result: Result<WeatherServerRecord, _> =
            serde_json::from_str(COMPLETE_DATA_SAMPLE);

        assert!(matches!(weather_record_parsing_result, Result::Ok(_)));

        let weather_record = weather_record_parsing_result.unwrap();
        assert_eq!(weather_record.station_id, "KEAT");
        assert!(matches!(weather_record.visibility, Option::Some(_)));

        let weather_visibility_value = weather_record.visibility.unwrap();
        assert!(matches!(
            weather_visibility_value,
            WeatherServerVisibility::Unrestricted(_)
        ));

        assert_eq!(weather_record.sky_coverage.len(), 1);
        assert_eq!(weather_record.sky_coverage[0].bases_altitude, 700);
        assert_eq!(weather_record.sky_coverage[0].coverage_type, "BKN");
    }

    const VISIBILITY_MISSING_WEATHER_SAMPLE: &str = r#"
    {
    "metar_id": 501717771,
    "icaoId": "KEAT",
    "receiptTime": "2024-02-22 14:16:27",
    "obsTime": 1708611180,
    "reportTime": "2024-02-22 14:13:00",
    "temp": 1.7,
    "dewp": 0.6,
    "wdir": 330,
    "wspd": 5,
    "wgst": null,
    "visib": null,
    "altim": 1024.8,
    "slp": null,
    "qcField": 6,
    "wxString": null,
    "presTend": null,
    "maxT": null,
    "minT": null,
    "maxT24": null,
    "minT24": null,
    "precip": null,
    "pcp3hr": null,
    "pcp6hr": null,
    "pcp24hr": null,
    "snow": null,
    "vertVis": null,
    "metarType": "SPECI",
    "rawOb": "KEAT 221413Z AUTO 33005KT 10SM BKN007 02\/01 A3026 RMK AO2 T00170006",
    "mostRecent": 1,
    "lat": 47.3975,
    "lon": -120.201,
    "elev": 375,
    "prior": 3,
    "name": "Wenatchee\/Pangborn Mem, WA, US",
    "clouds": [
      {
        "cover": "BKN",
        "base": 700
      }
    ]
  }
    "#;

    #[test]
    fn successful_parse_weather_record_with_missing_visibility() {
        let weather_record_parsing_result: Result<WeatherServerRecord, _> =
            serde_json::from_str(VISIBILITY_MISSING_WEATHER_SAMPLE);

        assert!(matches!(weather_record_parsing_result, Result::Ok(_)));

        let parsed_weather_data = weather_record_parsing_result.unwrap();
        assert!(matches!(parsed_weather_data.visibility, Option::None));
    }

    #[test]
    fn successful_parse_array_of_weather_records() {}
}
