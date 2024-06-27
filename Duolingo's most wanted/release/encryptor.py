#GLOBALS
alphabet_table = list()
seion = list()
R1 = 123
R2 = 987

def seion_maker():
    start = ['0x3042', '0x304b', '0x3055', '0x305f', '0x306a', '0x306f', '0x307e']

    row = list()
    for i in start:
        row.append(chr(int(i, 16)))
    seion.append(row)

    for i in range(4):
        row = list()
    
        for j in range(7):
            letter = ord(seion[i][j])
        
            if j==4 or j==6:
                letter += 1
            elif j==5:
                letter += 3
            elif j==3 and i==1:
                letter += 3
            else:
                letter += 2
                
            row.append(chr(letter))
        seion.append(row)

def alphabet_maker():
    alphabet = list(map(chr, range(97, 123))) + list(map(chr, range(49, 58)))
    for i in range(5):
        alphabet_table.append(alphabet[i*7 : i*7+7])

def scramble(x, y):
    row1 = x % 5
    row2 = y % 5

    if row1 != row2:
        alphabet_table[row1], alphabet_table[row2] = alphabet_table[row2], alphabet_table[row1]
    else:
        alphabet_table[row1].reverse()

    col1 = x % 7
    col2 = y % 7

    if col1 != col2:
        for i in range(5):
            alphabet_table[i][col1], alphabet_table[i][col2] = alphabet_table[i][col2], alphabet_table[i][col1]
    else:
        column = [alphabet_table[i][col1] for i in range(5)]
        column.reverse()
        for i in range(5):
            alphabet_table[i][col1] = column[i]

def Rgen():
    global R1, R2
    a = 19
    c = 10**3
    
    R1 = (R2 * a + R1) % c
    R2 = ((R1 << 3) & 0xFFFF) ^ (R1 >> 5) ^ (R1 << 2)
    
    return R1, R2

def encrypt(block):
    encrypted_block = ""
    for char in block:
        found = False
        for i in range(5):
            for j in range(7):
                if alphabet_table[i][j] == char:
                    encrypted_block += seion[i][j]
                    found = True
                    break
            if found:
                break
        if not found:
            encrypted_block += char
    
    scramble(R1, R2)
    return encrypted_block

def main():
    seion_maker()
    alphabet_maker()
    
    with open("secret_message.txt", "r") as input_file:
        input_text = (input_file.read()).lower().rstrip()
    
    blocks = [input_text[i:i+100] for i in range(0, len(input_text), 100)]
    encrypted_text = ""
    
    for block in blocks:
        encrypted_text += encrypt(block)
        global R1, R2
        R1, R2 = Rgen()
        
    with open("encrypted_message.txt", "w", encoding="utf-8") as output:
        output.write(encrypted_text)
    

main()

