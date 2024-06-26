use ciphers::{Cipher, Vigenere};
use std::io::{self, BufRead};
use std::{thread, time};

fn a(text: &str, key: &str) -> String {
    let mut encrypted_bytes: Vec<u8> = Vec::new();
    let text_bytes = text.as_bytes();
    let key_bytes = key.as_bytes();

    for (text_byte, key_byte) in text_bytes.iter().zip(key_bytes.iter().cycle()) {
        encrypted_bytes.push(text_byte ^ key_byte);
    }

    String::from_utf8_lossy(&encrypted_bytes).to_string()
}
#[no_mangle]
fn win() {
    let vigenere = Vigenere::new("examplekey");
    let text = "4.3*8)(&=;=!>\"#5:";
    let b = a(text, "exampleexapplekpy");
    let ptext = vigenere.decipher(&b).unwrap();
    println!("HCamp{{{}}}", ptext);
}

fn sike() {
    thread::sleep(time::Duration::from_secs(10000000000));
}
fn main() {
    println!("tell me a story\n");
    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let input = line.unwrap();

        if input.eq_ignore_ascii_case("stop")
            || input.eq_ignore_ascii_case("quit")
            || input.eq_ignore_ascii_case("exit")
            || input.trim() == "q"
        {
            break;
        }
        println!("{}", input);
    }

    sike();
    win();
}
