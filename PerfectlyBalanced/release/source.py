#!/usr/local/bin/python3

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

flag = b"HCamp{f4k3_fl4g}"
key = get_random_bytes(16)

def padded(pt):
    pad_len = -len(pt) % 16
    return pt + bytes([pad_len]) * pad_len

def padding(text, p):
    return p + text + p

if __name__ == '__main__':
    while True:
        x = input().encode()
        padded_flag = padded(padding(flag, x))

        cipher = AES.new(key, AES.MODE_ECB)
        encrypted = cipher.encrypt(padded_flag)

        print(encrypted.hex())