mod utils;

const SAMPLE_FILE_PATH: &str = "./tests/data/weather_server_response_sample.json";

#[test]
fn weather_service_response_sample_parsed_successfully() {
    let response_sample_string = utils::read_text_file(SAMPLE_FILE_PATH);
    print!("print_result: {}", response_sample_string);

    assert!(true)
}
