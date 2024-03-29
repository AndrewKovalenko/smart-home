use serde::{de, Deserialize, Deserializer};

#[derive(Debug, PartialEq)]
pub(crate) enum SkyCoverage {
    Clear,
    Few,
    Scattered,
    Broken,
    Overcast,
    Obscured,
}

impl<'de> Deserialize<'de> for SkyCoverage {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let s = String::deserialize(deserializer)?;
        let value = s.as_str();
        match value {
            "CLR" => Ok(SkyCoverage::Clear),
            "FEW" => Ok(SkyCoverage::Few),
            "SCT" => Ok(SkyCoverage::Scattered),
            "BKN" => Ok(SkyCoverage::Broken),
            "OVC" => Ok(SkyCoverage::Overcast),
            "OVX" => Ok(Self::Obscured),
            _ => Err(anyhow::anyhow!("unknown sky coverage type {}", value))
                .map_err(de::Error::custom),
        }
    }
}

#[derive(Deserialize, Debug)]
#[serde(untagged)]
pub(crate) enum WeatherServerVisibility {
    Unrestricted(String),
    Specific(f32),
}

#[derive(Deserialize, Debug)]
pub(crate) struct CloudLayer {
    #[serde(rename = "cover")]
    pub coverage_type: SkyCoverage,

    #[serde(rename = "base")]
    pub bases_altitude: Option<u16>,
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
        assert_eq!(weather_record.sky_coverage[0].bases_altitude.unwrap(), 700);
        assert_eq!(
            weather_record.sky_coverage[0].coverage_type,
            SkyCoverage::Broken
        );
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
    fn successful_parse_array_of_weather_records() {
        let multiple_stations_sample = format!(
            "[{}, {}]",
            COMPLETE_DATA_SAMPLE, VISIBILITY_MISSING_WEATHER_SAMPLE
        );

        let weather_data_parsing_result: Result<Vec<WeatherServerRecord>, _> =
            serde_json::from_str(&multiple_stations_sample);

        assert!(matches!(weather_data_parsing_result, Result::Ok(_)));

        let weather_data_records = weather_data_parsing_result.unwrap();
        assert_eq!(weather_data_records.len(), 2);
    }
}
