use anyhow::Ok;

use crate::dtos::weather_category::WeatherCategoryData;
use crate::repositories::weather_data_repository::get_weather_data_for_stations;

pub async fn get_weather_category_for_stations<'a>(
    station_ids: &[&'a str],
) -> Result<Vec<WeatherCategoryData>, anyhow::Error> {
    let weather_data_records = get_weather_data_for_stations(station_ids).await?;
    let station_weather_categories = weather_data_records
        .iter()
        .map(WeatherCategoryData::from)
        .collect();

    Ok(station_weather_categories)
}
