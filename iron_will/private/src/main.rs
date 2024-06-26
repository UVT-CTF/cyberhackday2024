use serde::{Deserialize, Serialize};
use serde_json;
use std::{
    fs::{self, File},
    io::{BufRead, BufReader},
    path::Path,
};

#[derive(Debug, Serialize, Deserialize)]
struct FileData {
    name: String,
    file_names: Vec<String>,
}

fn print_file_data(file_data: &FileData) {
    let slice_string_in_json_format = serde_json::to_string(&file_data);
    println!("{:?}", slice_string_in_json_format);
}

fn read_json_file(file_name: String) -> Result<Vec<FileData>, Box<dyn std::error::Error>> {
    let json_file_path = Path::new(&file_name);
    let mut files_data: Vec<FileData> = Vec::new();

    let file = File::open(json_file_path)?;
    for line in BufReader::new(file).lines() {
        let line = line.expect("couldn't get line");
        let file_data: FileData = serde_json::from_str(&line).expect("couldn't deserialize");
        files_data.push(file_data);
    }
    Ok(files_data)
}
fn bad() {
    let contents =
        fs::read_to_string("flag.txt").expect("Should have been able to read the file flag.txt");
    println!("{}", &contents);
}
fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();

    let dir = &args[1];
    let read_data = read_json_file(dir.to_string())?;
    for file_data in read_data {
        if file_data.name == "25a8d34a10b1910b1f31f934853c7959.zip" {
            bad();
        } else {
            println!("No flag for you. I am still hungry.give me my fovorite kind of food, but I won't tell you what it is")
        }
        print_file_data(&file_data);
    }

    Ok(())
}
