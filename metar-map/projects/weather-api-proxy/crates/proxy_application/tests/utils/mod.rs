use std::fs;

pub fn read_text_file(file_path: &str) -> String {
    let file_content = fs::read_to_string(file_path).unwrap();

    file_content
}
