#!/usr/local/bin/python3

import random
import os

flag = os.environ['FLAG']

def genSol(n):
    opposite = [1, 0, 3, 2]
    frequency = [0, 0, 0, 0]
    moves = [[0, 0]]
    sol = []
    r = random.randint(0, 100) % 4
    sol.append(r)
    i = 0
    j = 0
    match r:
        case 0:
            j -= 1
        case 1:
            j += 1
        case 2:
            i -= 1
        case 3:
            i += 1
    moves.append([i, j])

    k = 2
    stop = 0
    while k < n:
        i = moves[k - 1][0]
        j = moves[k - 1][1]
        r = random.randint(0, 100) % 4
        match r:
            case 0:
                j -= 1
            case 1:
                j += 1
            case 2:
                i -= 1
            case 3:
                i += 1

        if stop == 10:
            break

        if [i, j] not in moves:
            if (([i + 1, j] not in moves) or ([i + 1, j] == moves[k - 1])) and (([i - 1, j] not in moves) or ([i - 1, j] == moves[k - 1])) and (([i, j + 1] not in moves) or ([i, j + 1] == moves[k - 1])) and (([i, j - 1] not in moves) or ([i, j - 1] == moves[k - 1])):
                sol.append(r)
                moves.append([i, j])
                k += 1
                stop = 0
        else:
            stop += 1

    return sol


def genMaze(sol):
    i = 0
    j = 0
    imin = 0
    jmin = 0
    imax = 0
    jmax = 0
    moves = [[0, 0]]
    for x in sol:
        match x:
            case 0:
                j -= 1
                moves.append([i, j])
                if jmin > j:
                    jmin = j
            case 1:
                j += 1
                moves.append([i, j])
                if jmax < j:
                    jmax = j
            case 2:
                i -= 1
                moves.append([i, j])
                if imin > i:
                    imin = i
            case 3:
                i += 1
                moves.append([i, j])
                if imax < i:
                    imax = i

    if imin < 0:
        for k in range(len(moves)):
            moves[k][0] -= imin
        imax -= imin

    if jmin < 0:
        for k in range(len(moves)):
            moves[k][1] -= jmin
        jmax -= jmin

    maze = []
    for k in range(imax + 1):
        maze.append([0]*(jmax + 1))

    for i, j in moves:
        maze[i][j] = 1

    i, j = moves[0]
    maze[i][j] = 8

    return maze


def convertedSol(sol):
    s = ""
    for x in sol:
        match x:
            case 0:
                s += 'a'
            case 1:
                s += 'd'
            case 2:
                s += 'w'
            case 3:
                s += 's'

    return s


WELCOME="""
Welcome!
You have to escape this place!
You are given a path that you must follow! But be very carefull, one wrong step it's all it takes to lose yourself!

To succeed you have to enter the correct sequence of steps to get to the end!
w - Up
a - Left
s - Down
d - Right

Example:
s - Starting Point
# # # # # # # # # #
# s # # # # # # # #
#         # #     #
# # # #   # #   # #
# # # #   # #   # #
# # # #         # #
# # # # # # # # # #
Correct sequence:
sdddsssdddwwwd

Press Enter to continue!
"""

if __name__ == '__main__':
    print(WELCOME, end="")
    input()

    while True:
        resume = 0
        for level in range(25):
            print(f"LEVEL {level + 1}")
            if level < 10:
                sol = genSol(10)
            elif level < 20:
                sol = genSol(25)
            else:
                sol = genSol(50)

            # print(convertedSol(sol))
            maze = genMaze(sol)
            for i in range(len(maze[0]) + 2):
                print("#", end=" ")
            print()
            for line in maze:
                print("#", end=" ")
                for x in line:
                    if x == 0:
                        print("#", end=" ")
                    elif x == 1:
                        print(" ", end=" ")
                    else:
                        print("s", end=" ")
                print("#")
            for i in range(len(maze[0]) + 2):
                print("#", end=" ")
            print()

            print("Enter sequence: ")
            user_input = input()
            if user_input != convertedSol(sol):
                print("WRONG!")
                resume = 1
                break

        if resume != 1:
            print("Congratulation!")
            print(flag)
            break
