use super::weather_server_record::WeatherServerRecord;
use serde::Serialize;

#[derive(Serialize)]
pub struct WeatherCategory {
    pub station_id: String,
    pub weather_category: String,
}

impl From<&WeatherServerRecord> for WeatherCategory {
    fn from(value: &WeatherServerRecord) -> Self {
        WeatherCategory {
            station_id: value.station_id.clone(),
            weather_category: String::from("test"),
        }
    }
}
