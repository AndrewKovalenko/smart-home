use std::collections::HashMap;
use tokio;

use axum::{
    extract::Query,
    {http::StatusCode, routing::get, Json, Router},
};

#[tokio::main]
async fn main() {
    let web_app = Router::new().route(
        "/getWeatherCategoriesForStations",
        get(get_weather_categories_for_stations),
    );

    let io_listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(io_listener, web_app).await.unwrap();
}

async fn get_weather_categories_for_stations(
    stations: Query<HashMap<String, String>>,
) -> (StatusCode, Json<HashMap<String, String>>) {
    let result = stations.iter().fold(
        HashMap::new(),
        |mut result, (parameter_name, parameter_value)| {
            result.insert((*parameter_name).clone(), (*parameter_value).clone());
            result
        },
    );

    (StatusCode::OK, Json(result))
}
