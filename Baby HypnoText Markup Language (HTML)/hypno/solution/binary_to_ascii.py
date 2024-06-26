# run this script after running solve.py and getting flag.txt

# read binary data from "flag.txt"
with open("flag.txt", 'r') as f:
    binary_no = f.read().strip() 

flag = []

# every 8 bits corresponds to an ascii character
for i in range(0, len(binary_no), 8):
    
    ascii_char = binary_no[i:i+8]
    # convert to base 10 from base 2
    decimal_representation = int(ascii_char, 2)
    # add the character corresponding to the decimal representation to flag list
    flag += chr(decimal_representation)

# transform flag list into string
string_flag = "".join(flag)

print(string_flag)
