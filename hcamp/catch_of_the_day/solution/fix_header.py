with open("flag.png", "rb") as f:
  file = f.read()

png_header = b'\x89PNG\r\n\x1a\n'

header_start = file.find(png_header)

# if header was found
if header_start != -1:
  good_file = file[header_start:]


with open("flag_fixed.png", "wb") as f2:
  file = f2.write(good_file)
  print("Fixed file created!")