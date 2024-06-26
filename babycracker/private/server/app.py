from flask import Flask, request, jsonify
import os

app = Flask(__name__)

flag = os.getenv("FLAG", "HCamp{9c44a1237cd5cd94bc293029b496da6181cc656aba93af5350a4fed7d211d8be}")

@app.route("/", methods=["POST"])
def check_password():
    password = request.form.get("password", "")
    if password == "aaa9402664f1a41f40ebbc52c9993eb66aeb366602958fdfaa283b71e64db123":
        return jsonify({"flag": flag})
    elif password == "":
        return jsonify({"error": "The \"password\" parameter has not been set"}), 400
    else:
        return jsonify({"error": "Incorrect password"}), 400
    
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)