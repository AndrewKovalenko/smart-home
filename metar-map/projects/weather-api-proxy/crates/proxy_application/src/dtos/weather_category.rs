use serde::Serialize;

#[derive(Serialize)]
pub struct WeatherCategory {
    pub station_id: String,
    pub weather_category: String,
}
