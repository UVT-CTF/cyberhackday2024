import hashlib
import random
import string

PASSWORD = "r#Ndqk#Vye#&B*G21yjGF8pnT)Ng!mnta1xHdBeRFiZ6ch0)V9Bt9RWF2B1PN^848xn@YHVv6wu8U-3r"
FLAG = "HCamp{cf9738b889960f321f5eaf25ed7bb878d24934f58cc7a86b446930b980fb492f}"
DIFFICULTY = 6

def verify_proof_of_work(challenge, nonce):
    target = '0' * DIFFICULTY
    text = f"{challenge}{nonce}".encode('utf-8')
    hash_result = hashlib.sha256(text).hexdigest()
    return hash_result.startswith(target)

def generate_challenge_string(length=16):
    characters = string.ascii_letters + string.digits
    return ''.join(random.choice(characters) for _ in range(length))

def main():
    challenge = generate_challenge_string()
    print(f"Generated challenge string: {challenge}")

    nonce = int(input("Enter the nonce: "))
    
    if not verify_proof_of_work(challenge, nonce):
        print("Invalid proof of work. Try again.")
        return

    pw = input("Enter the password: ")

    if pw == PASSWORD:
        print(f"Flag: {FLAG}")
    else:
        print("Incorrect password. Try harder!")

if __name__ == "__main__":
    main()
