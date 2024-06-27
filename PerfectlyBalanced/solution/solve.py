from pwn import *
from math import lcm

conn = remote("host", 12345)

flag_size = 49

charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}_-!?"
plaintext = ""
while len(plaintext) < flag_size:
    for c in charset:
        x = c + plaintext
        size = len(x)
        times = lcm(size, 16) // size + 1
        x = x * times + (-flag_size % 16)*" "

        conn.sendline(x.encode())
        encrypted = conn.recvline()

        if encrypted[:32] == encrypted[len(x)*2 + (flag_size*2 - size*2):len(x)*2 + (flag_size*2 - size*2) + 32]:
            plaintext = c + plaintext
            break

print(plaintext)

conn.interactive()