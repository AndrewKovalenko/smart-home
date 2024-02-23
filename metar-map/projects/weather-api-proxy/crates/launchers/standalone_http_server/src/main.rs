use std::collections::HashMap;
use tokio;

use axum::{
    extract::Query,
    {http::StatusCode, routing::get, Json, Router},
};

use proxy_application::{
    dtos::weather_category::WeatherCategory,
    services::weather_service::get_weather_category_for_stations,
};

const SERVER_URL: &str = "0.0.0.0:3000";
const STATION_ID_SEPARATOR: &str = ",";
const STATIONS_PARAMETER_NAME: &str = "stations";

#[tokio::main]
async fn main() {
    let web_app = Router::new().route(
        "/getWeatherCategoriesForStations",
        get(get_weather_categories_for_stations),
    );

    let io_listener = tokio::net::TcpListener::bind(SERVER_URL).await.unwrap();
    axum::serve(io_listener, web_app).await.unwrap();
}

async fn get_weather_categories_for_stations(
    query_parameters: Query<HashMap<String, String>>,
) -> (StatusCode, Json<Vec<WeatherCategory>>) {
    let station_ids_query_parameter = query_parameters.get(STATIONS_PARAMETER_NAME);

    if station_ids_query_parameter == Option::None
        || !station_ids_query_parameter
            .unwrap()
            .contains(STATION_ID_SEPARATOR)
    {
        return (StatusCode::UNPROCESSABLE_ENTITY, Json(Vec::new()));
    }

    let station_ids = station_ids_query_parameter
        .unwrap()
        .split(STATION_ID_SEPARATOR)
        .collect::<Vec<&str>>();

    let weather_categories = get_weather_category_for_stations(station_ids.as_slice())
        .await
        .unwrap();

    (StatusCode::OK, Json(weather_categories))
}
