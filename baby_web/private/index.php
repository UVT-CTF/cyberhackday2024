<?php

include 'flag.php';

if (isset($_COOKIE['admin']) && $_COOKIE['admin'] === 'true') {
//check user agent header
//check also admin cookie
    if (isset($_SERVER['HTTP_USER_AGENT']) && $_SERVER['HTTP_USER_AGENT'] === 'uvt-ctf') {

        echo "Access granted! The flag is: " . $flag;
    } else {
        show_source(__FILE__);
    }
} else {
    show_source(__FILE__);
}
?>
