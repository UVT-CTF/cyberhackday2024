import json

# Define the file containing the JSON strings
file_path = 'json_data'

# Read the JSON strings from the file
with open(file_path, 'r') as file:
    lines = file.readlines()

# Initialize the list for RGB values
rgb_values = []

# Parse the JSON strings to extract RGB values
for line in lines:
    try:
        data = json.loads(line)
        r = data['params']['r']
        g = data['params']['g']
        b = data['params']['b']
        rgb_values.append([r, g, b])
    except (json.JSONDecodeError, KeyError) as e:
        print(f"Error parsing line: {line} - {e}")
        continue

# Print the RGB values in the desired format
for rgb in rgb_values:
    print(rgb)

# Optionally, you can save these values to a new file if needed
output_file_path = 'pixels1.txt'
with open(output_file_path, 'w') as file:
    for rgb in rgb_values:
        file.write(f"{rgb}\n")

print("RGB values extracted and saved successfully.")
