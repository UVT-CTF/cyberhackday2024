from PIL import Image

# Define the desired resolution
width, height = 50, 50

# Read the RGB values from the file
with open('pixels1.txt', 'r') as file:
    lines = file.readlines()

# Initialize the matrix
rgb_matrix = []

# Parse the RGB values, handling potential formatting issues
for line in lines:
    # Remove brackets and split by commas
    clean_line = line.strip().replace("[", "").replace("]", "")
    # Split by commas and remove extra spaces
    parts = [part.strip() for part in clean_line.split(',')]
    # Convert to integers and add as a tuple to the list
    try:
        rgb_tuple = tuple(map(int, parts))
        rgb_matrix.append(rgb_tuple)
    except ValueError:
        print(f"Error parsing line: {line}")
        continue

# Check if we have enough values to fill the image
print(len(rgb_matrix))
input()
if len(rgb_matrix) < width * height:
    raise ValueError("Not enough RGB values to fill the image")

# Create a new image with the appropriate size
image = Image.new('RGB', (width, height))

# Fill the image with the RGB values from the matrix
for i in range(height):
    for j in range(width):
        index = i * width + j
        rgb = rgb_matrix[index]
        image.putpixel((j, i), rgb)

# Save the image
image.save('output_image.png')

print("Image created and saved as 'output_image.png'")
