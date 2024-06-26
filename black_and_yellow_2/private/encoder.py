import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import PIL.Image as pim
import numpy as np
image = pim.open('black_and_yellow.png')
img = np.asarray(image)

a,b,_c=img.shape
yellow =[255,255,0]
black =[0 ,0 ,0]
def encode_batch(example):
    batch = example.replace(' ','')	
    for k,c in enumerate(batch):
        print(c,k)
        i,j = np.random.randint(0,a,(2))
        nimg = np.copy(img)
        nimg[i,j] = np.array(yellow) if c=='1' else np.array(black)

        pim.fromarray(nimg).save(f"./f/black_and_yellow_{k}.png")

        



example='01001000 01000011 01100001 01101101 01110000 01111011 01111001 01101111 01110101 01011111 01100100 01100101 01110011 01100101 01110010 01110110 01100101 01011111 01110100 01101000 01101001 01110011 01111101'
encode_batch(example)
