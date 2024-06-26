import PIL.Image as pim
def decode():
    data = b""
    for k in range(184):
        name = f"./f/black_and_yellow_{k}.png"
        image = pim.open(name)
        width,heigth = image.size
        for i in range(0,width):
            for j in range(0,heigth):
                pixel = image.getpixel((i,j))
                
                if pixel == (0 ,0 ,0):
                    data +=b'0'
                elif pixel == (255,255,0):
                    data +=b'1'
        print(data,k)
    print(''.join(chr(int(data[i*8:i*8+8],2)) for i in range(len(data)//8)))
        
                    
decode()

