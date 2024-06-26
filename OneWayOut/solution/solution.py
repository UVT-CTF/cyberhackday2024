from pwn import *

conn = remote("host", 12345)

conn.recvuntil(b"Press Enter to continue!")
conn.sendline(b"")

for level in range(25):
    conn.recvuntil(b"LEVEL")
    conn.recvuntil(b"\n")

    maze = []
    line = conn.recvline()
    while line != b"Enter sequence: \n":
        line = line.decode().strip()
        tmp = []
        for i in range(len(line) // 2 + 1):
            tmp.append(line[i*2])
        maze.append(tmp)
        line = conn.recvline()

    # for l in maze:
    #     print(l)

    starti = 0
    startj = 0
    for i in range(len(maze)):
        found = 0
        for j in range(len(maze[0])):
            if maze[i][j] == 's':
                starti = i
                startj = j
                found = 1
                break
        if found == 1:
            break

    # print(starti, startj)

    previ = 0
    prevj = 0
    i = starti
    j = startj  
    sol = ""
    while True:
        if maze[i][j - 1] == " " and (i != previ or j - 1 != prevj):
            previ = i
            prevj = j
            j -= 1
            sol += 'a'
        elif maze[i][j + 1] == " " and (i != previ or j + 1 != prevj):
            previ = i
            prevj = j
            j += 1
            sol += 'd'
        elif maze[i - 1][j] == " " and (i - 1 != previ or j != prevj):
            previ = i
            prevj = j
            i -= 1
            sol += 'w'
        elif maze[i + 1][j] == " " and (i + 1 != previ or j != prevj):
            previ = i
            prevj = j
            i += 1
            sol += 's'
        else:
            break

    conn.sendline(sol.encode())

conn.interactive()