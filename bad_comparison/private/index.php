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

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    if (login($username, $password)) {
        echo "Logged in as $username\n Here is your flag: HCamp{b3255a66ffbb5f996b62e907c857f0609c95a1eabb9762c9b3ca52899b181682}";
    } else {
        echo "Invalid login!";
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
    </div>
</body>
</html>
