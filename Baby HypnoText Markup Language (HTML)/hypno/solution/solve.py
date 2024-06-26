target_seq1 = "<img src"
target_seq2 = "<img width"

content = ""

with open("hypnotherapy.html", 'r') as f:
    for line in f:
        if line.startswith(target_seq1):
            content += "1"  # append 1 to content if line starts with "<img src"
        elif line.startswith(target_seq2):
            content += "0"  # append 0 to content if line starts with "<img width"


with open("flag.txt", 'w') as f:
    f.write(content)

print("Saved the important stuff!")