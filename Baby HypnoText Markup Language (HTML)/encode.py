a = {1:'<img src="maxresdefault.png" width="800" height="800">', 0:'<img width="800" src="maxresdefault.png" height="800">'}

flag = 'HCamp{I_hOPE_YOUr_EYEs_DiDnT_RuN_AwAy}'

binary = ''.join(format(ord(i), '08b') for i in flag)
with open('hypnotherapy.html','w') as file:
    file.writelines('''<!DOCTYPE html>
<html>
<head>
    <title>Hypnosis</title>
    <body style="background-color:powderblue;">
    <style>
        body {
            font-family: 'Comic Sans MS', cursive, sans-serif;
            background-color: #f0f8ff;
            text-align: center;
            color: #333;
        }
        h1 {
            color: #ff69b4;
            font-size: 3em;
        }
        p {
            font-size: 1.2em;
        }
        img {
            border: 5px solid #ff69b4;
            border-radius: 10px;
            margin: 10px;
        }
    </style>
</head>
<body>
    <h1>Hypnosis</h1>
    <p>You are getting sleepy...</p>
    <p>You are getting very sleepy...</p>
    <p>You are getting very very sleepy...</p>
    <p>You are getting very very very sleepy...</p>
    <p>You are getting very very very very sleepy...</p>
    <p>You are getting very very very very very sleepy...</p>
    <p>You are getting very very very very very very sleepy...</p>
    <p>You are getting very very very very very very very sleepy...</p>
    <p>You are getting very very very very very very very very sleepy...</p>
    <p>You are getting very very very very very very very very very sleepy...</p>
    <p>Now, do you see your card here?</p>
    <p>No.</p>
    <p>That's because you're looking too closely.</p>
    <p>And what have I been telling you all night?</p>
    <p>The closer you look...</p>
    <p><strong>The less you see.</strong></p>
''')

    for l in binary:
        file.writelines(a[int(l)])
        file.write("\n")

    file.write('''</body>
</html>''')