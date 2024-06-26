with open ("serenade4you.wav", "rb") as f:
  file = f.read()

# Byte corresponding to 'R'
good_byte = b'\x52'

# Replace the first byte of the header with the correct one for .wav files
file_good = good_byte + file[1:]

with open ("serenade4you_fixed.wav", "wb") as f2:
  file = f2.write(file_good)
  print("Fixed file created!")