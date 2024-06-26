import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import PIL.Image as pim
import numpy as np
import os
print(os.getcwd())
image = pim.open('black_and_yellow.png')
img = np.asarray(image)
a,b,_c=img.shape
yellow =[255,255,0]
black =[0 ,0 ,0]

#img = mpimg.imread('black_and_yellow.png')
def replace_by():
    for i,row in enumerate(img):
        for j,pixel in enumerate(row):
            if list(pixel) in(black,yellow):
                img[i,j]= np.array([255,255,255])
replace_by()
def encode():
    data = "01001000 01000011 01100001 01101101 01110000 01111011 01101110 01101111 01011111 01110011 01101111 01101110 01100111 01011111 01110010 01100101 01100110 01011111 01101000 01100101 01110010 01100101 01111101"

    i,j=0,0
    for c in data:
        match c:
            case '0':
                img[i,j]=np.array(black)
                j+=128
            case '1':
                img[i,j]=np.array(yellow)
                j+=128
            case ' ':
                j=0
                i+=16
        pim.fromarray(img).save("black_and_yellow_-1.png")
def encode_batch():
    batch = "01100011 01000111 00111001 01110011 01100001 01010111 01001110 00110000 01011010 01101110 01110100 01101001 01100010 01000100 01010010 01101010 01100001 00110001 00111001 01110110 01100011 01101100 00111001 00110101 01001101 01111010 01000101 01111000 01001101 01001000 01100100 00111001"
    for k,c in enumerate(batch):
        i,j = np.random.randint(0,a,(2))
        nimg = np.copy(img)
        nimg[i,j] = np.array(yellow) if c=='1' else np.array(black)
        pim.fromarray(nimg).save(f"./f/black_and_yellow_{k}.png")

        




encode()
