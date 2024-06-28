<?php
session_start();

$users = [
    ['username' => 'admin', 'password' => 'SuperSecretPassword123!_HUIHIUSHDFIUSHFIUSHDFIUSHDFUIS'],
    ['username' => 'user', 'password' => 'user123'],
];

function login($username, $password) {
    global $users;

    foreach ($users as $user) {
        if ($user['username'] === $username && !strcmp($password, $user['password'])) {
            $_SESSION['loggedin'] = true;
            $_SESSION['username'] = $username;
            return true;
        }
    }
    return false;
}

$message = "";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    if (login($username, $password)) {
        $message = "<div class='success'>Logged in as $username<br>Here is your flag: <span class='flag'>HCamp{b3255a66ffbb5f996b62e907c857f0609c95a1eabb9762c9b3ca52899b181682}</span></div>";
    } else {
        $message = "<div class='error'>Invalid login!</div>";
    }
}

if (isset($_GET['testpwd'])) {
    $input = $_GET['testpwd'];
    if (!strcmp($input, "SuperSecretPassword123!_HUIEWHIUFBDJKHIOUJKKIUSHJASD")) {
        echo "";
    } else {
        echo "No Real Password";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link rel="stylesheet" href="style.css">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }
        .login-container {
            background: #fff;
            padding: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }
        .login-container h2 {
            margin-bottom: 20px;
        }
        .login-container form {
            display: flex;
            flex-direction: column;
        }
        .login-container label {
            margin-bottom: 5px;
        }
        .login-container input[type="text"], 
        .login-container input[type="password"] {
            padding: 10px;
            margin-bottom: 20px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        .login-container input[type="submit"] {
            padding: 10px;
            border: none;
            border-radius: 4px;
            background-color: #28a745;
            color: #fff;
            font-size: 16px;
            cursor: pointer;
        }
        .login-container input[type="submit"]:hover {
            background-color: #218838;
        }
        .message {
            margin-top: 20px;
        }
        .error {
            color: #ff0000;
        }
        .success {
            color: #28a745;
        }
        .flag {
            font-weight: bold;
            color: #0000ff;
            animation: blink 1s step-end infinite;
        }
        @keyframes blink {
            50% {
                opacity: 0;
            }
        }
    </style>
</head>
<body>
    <div class="login-container">
        <h2>Login</h2>
        <form method="POST">
            <label for="username">Username</label>
            <input type="text" id="username" name="username" required>
            <label for="password">Password</label>
            <input type="password" id="password" name="password" required>
            <input type="submit" value="Login">
        </form>
        <div class="message"><?php echo $message; ?></div>
    </div>
</body>
</html>
