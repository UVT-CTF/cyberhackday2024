import os
import subprocess
import sys

if __name__ == "__main__":
    if not os.path.isfile("youtube-shorts.pcap"):
        print("Put the pcap file in the same directory as this script.")
        sys.exit(1)
    
    strings_process = subprocess.Popen(["strings", "youtube-shorts.pcap"], stdout=subprocess.PIPE)
    grep_process = subprocess.Popen(["grep", "SENhbXB7NTNhZTIwZTJmMDljMTM0YjIwN2Y4OWQ3MWVhYTJlMTlkOGE5NDU5ZTBjOWFiZDZmMDQxOGVlYjFiNTdhNDNkNX0="], stdin=strings_process.stdout, stdout=subprocess.PIPE)
    strings_process.stdout.close()
    output, error = grep_process.communicate()
    
    print(output.decode())
    
    print("Now we need to decode the base64 string.")
    
    base64_process = subprocess.Popen(["base64", "-d"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    output, error = base64_process.communicate(input=b"SENhbXB7NTNhZTIwZTJmMDljMTM0YjIwN2Y4OWQ3MWVhYTJlMTlkOGE5NDU5ZTBjOWFiZDZmMDQxOGVlYjFiNTdhNDNkNX0=")
    
    print(f"\nFlag: {output.decode()}")
