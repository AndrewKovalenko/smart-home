use serde::Deserialize;

#[derive(Deserialize)]
#[serde(untagged)]
pub(crate) enum WeatherServerVisibility {
    Unrestricted(String),
    Defined(u8),
    Undefined(i8),
}

#[derive(Deserialize)]
pub(crate) struct CloudLayer {
    pub coverage_type: String,
    pub bases_altitude: String,
}

#[derive(Deserialize)]
pub(crate) struct WeatherServerRecord {
    pub station_id: String,
    pub visibility: WeatherServerVisibility,
    pub sky_coverage: Vec<CloudLayer>,
}
