import hashlib

DIFFICULTY = 6

def proof_of_work(challenge):
    target = '0' * DIFFICULTY
    nonce = 0
    while True:
        text = f"{challenge}{nonce}".encode('utf-8')
        hash_result = hashlib.sha256(text).hexdigest()
        if hash_result.startswith(target):
            return nonce
        nonce += 1

def main():
    challenge = input("Enter the challenge string: ")
    print("Calculating Proof of Work. This might take some time...")
    nonce = proof_of_work(challenge)
    print(f"Proof of Work successful! Nonce found: {nonce}")

if __name__ == "__main__":
    main()
