import PIL.Image as pim
def decode():
    print("start")
    data = b""
   
    name = "black_and_yellow_-1.png"
    image = pim.open(name)
    width,heigth = image.size
    for i in range(0,heigth):
        for j in range(0,width):
            pixel = image.getpixel((j,i))
            
            if pixel == (0 ,0 ,0):
                data +=b'0'
            elif pixel == (255,255,0):
                data +=b'1'
            print(data)
    print(''.join(chr(int(data[i*8:i*8+8],2)) for i in range(len(data)//8)))
    	
        
                    
decode()

