use crate::dtos::weather_category::WeatherCategory;

pub fn get_weather_category_for_stations<'a>(station_ids: &[&'a str]) -> Vec<WeatherCategory> {
    let weather_categories = station_ids
        .iter()
        .map(|station_id| WeatherCategory {
            station_id: String::from(*station_id),
            weather_category: String::from("VFR"),
        })
        .collect();

    weather_categories
}
