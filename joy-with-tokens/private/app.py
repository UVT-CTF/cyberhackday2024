from flask import Flask, request
import jwt
import time
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(24)

with open('priv.pem', 'r') as f:
    private_key = f.read()

with open('pub.pem', 'r') as f:
    public_key = f.read()

with open('flag.txt', 'r') as f:
    flag = f.read()

@app.route("/get_token")
def get_token():
    token = jwt.encode({'admin': False, 'now': time.time()}, private_key, algorithm='RS256')
    return token

@app.route("/get_flag", methods=['POST', 'GET'])
def get_flag():
    if request.method == 'GET':
        return """
    <h1>Please POST me a JWT token! Don't expect me to give out the flag for free!</h1>
    <p>NOTE TO SELF: I should probably check if the token is expired or invalid...</p>
    """, 403
    
    
    try:
        payload = jwt.decode(request.form['jwt'], public_key, algorithms=['RS256'])
        if payload.get('admin'):
            return flag
        else:
            return "Access Denied", 403
    except jwt.ExpiredSignatureError:
        return "Token has expired", 401
    except jwt.InvalidTokenError:
        return "Invalid token", 401

@app.route("/")
def sauce():
    return f"""
    <code>
    {open(__file__).read()}
    </code>
"""

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
