DNS rebinding 

`gethostbyname($parsedUrl['host']);` 
is called after 
`@file_get_contents($url, false, $context);`

Allowing us to exploit this by using the `DNS rebinding tehnique`, it could be pointing to `localhost` in `gethostbyname`, and then when `file_get_contents` resolves it, use an `arbitrary ip`
