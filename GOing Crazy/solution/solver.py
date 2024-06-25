from Crypto.Cipher import ARC4
import binascii

def rc4_decrypt(cipher_hex, key_hex):
    cipher_bytes = binascii.unhexlify(cipher_hex)
    key_bytes = binascii.unhexlify(key_hex)

    cipher = ARC4.new(key_bytes)
    decrypted_bytes = cipher.decrypt(cipher_bytes)
    
    return decrypted_bytes

if __name__ == "__main__":
    cipher_hex = "b308e7b6dac4a2d9af921646c26b25c8456fb111b40cde89970648bbf1f4"
    key_hex = "238faeb6389c9d150ebc"

    decrypted_bytes = rc4_decrypt(cipher_hex, key_hex)
    print("Decrypted text:", decrypted_bytes.decode())
