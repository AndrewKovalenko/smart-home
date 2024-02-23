use crate::dtos::weather_server_record::WeatherServerRecord;
use anyhow;
use reqwest;

const STATIONS_URL_SEPARATOR: &str = ",";

pub(crate) fn get_weather_data_for_stations(
    stationIds: &[&str],
) -> anyhow::Result<Vec<WeatherServerRecord>> {
    let weather_server_request_url = format!(
        "https://aviationweather.gov/api/data/metar?ids={}&format=json&hours=0",
        stationIds.join(STATIONS_URL_SEPARATOR)
    );
    let weather_data_server_response = reqwest::blocking::get(weather_server_request_url)?;

    let weather_data_string = weather_data_server_response.text()?;
    let weather_data = serde_json::from_str(&weather_data_string)?;

    anyhow::Result::Ok(weather_data)
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEST_STATION_IDS: &str = 
    "KEAT,KELN,KSMP,KPLU,KRNT,KBFI,KSEA,KTIW,KTCM,KGRF,KPWT,KOLM,KSHN,KHQM,KUIL,KCLM,CYYJ,KFHR,KORS,KBLI,KBVS,KNUW,K0S9,KPAE,KAWO,KS52";

    #[test]
    fn successful_weather_service_call() {
        let station_ids = TEST_STATION_IDS.split(",").collect::<Vec<&str>>();
        let weather_data_request = get_weather_data_for_stations(&station_ids);

        assert!(matches!(weather_data_request, Result::Ok(_)));
        assert_eq!(station_ids.len(), weather_data_request.unwrap().len());
    }
}
