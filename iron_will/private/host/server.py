import socket
import subprocess

print("start", flush=True)

listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
listener.bind(('0.0.0.0', 12345))  
listener.listen(5)
print(listener.getsockname(), flush=True)

try:
    while True:
        client, addr = listener.accept()
        print("got client", flush=True)
        
        
        data = client.recv(4096) 
        
        
        with open('temp', 'wb') as file:
            file.write(data)
        print("wrote file", flush=True)
        
        subprocess.Popen("./iron_will temp", shell=True, stdin=client, stdout=client, stderr=client)
        
        client.close()
except KeyboardInterrupt:
    pass
finally:
    listener.close()
