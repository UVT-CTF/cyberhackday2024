import ctypes
import string
from datetime import datetime

PASSWORD_LENGTH = 80
CHARSET = string.ascii_letters + string.digits + "!@#$%^&*()-_=+"

def generate_password(seed):
    libc = ctypes.CDLL("libc.so.6")
    
    libc.srand(seed)
    
    password = []
    for _ in range(PASSWORD_LENGTH):
        key = libc.rand() % len(CHARSET)
        password.append(CHARSET[key])
    
    return ''.join(password)

def main():
    start_timestamp = int(datetime(2023, 2, 1, 0, 0, 0).timestamp())
    end_timestamp = int(datetime(2023, 2, 28, 23, 59, 59).timestamp())
    
    print("Searching for correct password...")
    for timestamp in range(start_timestamp, end_timestamp + 1):
        password = generate_password(timestamp)
        if password.startswith("r#Ndq"):
            print(f"Correct password found: {password}")
            print("Connect to the server and submit the password to get the flag.")
            return
        
    print("No correct password found")

if __name__ == "__main__":
    main()
