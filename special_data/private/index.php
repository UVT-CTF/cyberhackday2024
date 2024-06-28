<?php
function isAllowedIP($url, $allowedIP) {
    $parsedUrl = parse_url($url);
    
    if (!$parsedUrl || !isset($parsedUrl['host'])) {
        return false;
    }
    
    $hostIP = gethostbyname($parsedUrl['host']);
    
    return $hostIP === $allowedIP;
}

function fetchContent($url) {
    $context = stream_context_create([
        'http' => [
            'timeout' => 5 // Timeout in seconds
        ]
    ]);

    $content = @file_get_contents($url, false, $context);
    if ($content === FALSE) {
        $error = error_get_last();
        throw new Exception("Unable to fetch content from the URL. Error: " . $error['message']);
    }
    return $content;
}

$blacklistedFunctions = [
    'exec', 'shell_exec', 'system', 'passthru', 'popen', 'proc_open', 'pcntl_exec', 
    'eval', 'assert', 'create_function', 'include', 'include_once', 'require', 
    'require_once', 'dl', 'fopen', 'file_get_contents', 'file_put_contents', 
    'fsockopen', 'pfsockopen', 'curl_exec', 'curl_multi_exec', 'parse_ini_file', 
    'show_source', 'ini_set', 'ini_restore', 'apache_child_terminate', 'apache_setenv', 
    'define_syslog_variables', 'extract', 'parse_str', 'putenv', 'getenv', 'link', 
    'symlink', 'escapeshellarg', 'escapeshellcmd', 'pcntl_fork', 'pcntl_waitpid', 
    'pcntl_wait', 'pcntl_wifexited', 'pcntl_wifstopped', 'pcntl_wifsignaled', 
    'pcntl_wexitstatus', 'pcntl_wtermsig', 'pcntl_wstopsig', 'pcntl_signal', 
    'pcntl_alarm', 'pcntl_signal_dispatch', 'pcntl_get_last_error', 'pcntl_strerror', 
    'pcntl_sigprocmask', 'pcntl_sigwaitinfo', 'pcntl_sigtimedwait', 'pcntl_exec', 
    'pcntl_getpriority', 'pcntl_setpriority', 'proc_close', 'proc_get_status', 
    'proc_nice', 'proc_terminate', 'ini_alter', 'ini_get_all', 'ini_restore', 
    'openlog', 'syslog', 'readlink', 'realpath', 'set_time_limit', 'popen', 
    'passthru', 'proc_open', 'proc_close', 'proc_get_status', 'proc_nice', 
    'proc_terminate', 'stream_select', 'socket_select', 'socket_create', 
    'socket_create_listen', 'socket_create_pair', 'socket_getpeername', 
    'socket_getsockname', 'socket_set_block', 'socket_set_nonblock', 
    'socket_strerror', 'socket_bind', 'socket_listen', 'socket_accept', 
    'socket_connect', 'socket_strerror', 'socket_shutdown', 'socket_read', 
    'socket_write', 'socket_send', 'socket_sendto', 'socket_recv', 'socket_recvfrom', 
    'socket_close', 'socket_get_option', 'socket_set_option', 'socket_last_error', 
    'socket_clear_error', 'pcntl_alarm', 'pcntl_fork', 'pcntl_wait', 'pcntl_signal', 
    'pcntl_wifexited', 'pcntl_wexitstatus', 'pcntl_wifsignaled', 'pcntl_wtermsig', 
    'pcntl_wifstopped', 'pcntl_wstopsig', 'pcntl_exec', 'pcntl_signal_dispatch', 
    'pcntl_getpriority', 'pcntl_setpriority', 'pcntl_waitpid', 'pcntl_wifcontinued', 
    'pcntl_strerror', 'pcntl_sigprocmask', 'pcntl_sigwaitinfo', 'pcntl_sigtimedwait', 
    'pcntl_signal_get_handler', 'pcntl_async_signals', 'posix_kill', 'posix_mkfifo', 
    'posix_mknod', 'posix_setpgid', 'posix_setsid', 'posix_setuid', 'posix_seteuid', 
    'posix_setgid', 'posix_setegid', 'posix_setregid', 'posix_setreuid', 'posix_uname', 
    'posix_times', 'posix_ctermid', 'posix_get_last_error', 'posix_getegid', 'posix_geteuid', 
    'posix_getgid', 'posix_getuid', 'posix_getpgid', 'posix_getpgrp', 'posix_getpid', 
    'posix_getppid', 'posix_getsid', 'posix_isatty', 'posix_strerror', 'posix_initgroups', 
    'posix_getgrnam', 'posix_getgrgid', 'posix_getpwnam', 'posix_getpwuid', 'posix_setgroups', 
    'posix_getlogin', 'posix_getcwd', 'posix_access', 'posix_getrlimit', 'posix_getpgid', 
    'posix_getsid', 'posix_getlogin', 'posix_ttyname', 'posix_mknod', 'posix_mkfifo', 
    'posix_setgid', 'posix_setuid', 'posix_kill', 'posix_strerror', 'posix_ctermid', 
    'posix_isatty', 'posix_times', 'posix_ttyname', 'posix_uname', 'posix_setpgid', 
    'posix_getpgid', 'posix_setsid', 'posix_getpid', 'posix_getppid', 'posix_getsid', 
    'posix_setgid', 'posix_setuid', 'posix_seteuid', 'posix_setegid', 'posix_geteuid', 
    'posix_getegid', 'posix_getgroups', 'posix_setgroups', 'posix_setregid', 'posix_setreuid', 
    'posix_getpgrp', 'posix_getpwnam', 'posix_getpwuid', 'posix_getgrnam', 'posix_getgrgid', 
    'posix_initgroups', 'posix_get_last_error', 'posix_strerror', 'posix_getlogin', 
    'posix_getpgid', 'posix_getsid', 'posix_getlogin', 'posix_ttyname', 'posix_mknod', 
    'posix_mkfifo', 'posix_setgid', 'posix_setuid', 'posix_kill', 'posix_strerror', 
    'posix_ctermid', 'posix_isatty', 'posix_times', 'posix_ttyname'
];

$blacklistPattern = '/\b(' . implode('|', $blacklistedFunctions) . ')\b/i';

?>

<!DOCTYPE html>
<html>
<head>
    <title>CTF Challenge: Secure URL Fetch</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }
        .container {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            padding: 20px;
            max-width: 600px;
            text-align: center;
        }
        h1 {
            color: #333;
        }
        p {
            color: #666;
        }
        .message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 5px;
        }
        .message.success {
            background-color: #d4edda;
            color: #155724;
        }
        .message.error {
            background-color: #f8d7da;
            color: #721c24;
        }
        .message.info {
            background-color: #cce5ff;
            color: #004085;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>CTF Challenge: Secure URL Fetch</h1>
        <p>Provide a URL to fetch and execute its content if it's safe.</p>
        <p>Example: ?url=http://127.0.0.1/index.html</p>
        
        <?php
        if ($_SERVER['REQUEST_METHOD'] === 'GET' && isset($_GET['url'])) {
            $url = $_GET['url'];
            $allowedIP = '127.0.0.1';  
            
            if (isAllowedIP($url, $allowedIP)) {
                $content = fetchContent($url);
                if (preg_match($blacklistPattern, $content)) {
                    echo '<div class="message error">Content contains blacklisted functions. Execution halted.</div>';
                } else {
                    echo '<div class="message success">Content fetched and executed successfully:</div>';
                    echo '<div class="message info">' . htmlspecialchars($content) . '</div>';
                    $output = eval($content);
                }
            } else {
                echo '<div class="message error">Invalid URL or IP not allowed.</div>';
            }
        } else {
            echo '<br>';
            highlight_file(__FILE__);
        }
        ?>
    </div>
</body>
</html>
