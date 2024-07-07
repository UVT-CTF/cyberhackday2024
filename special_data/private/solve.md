#INTENDED

Bypass filters by using data URLs

https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs

by providing invalid mediatype, the first part is ignored, 
and the ip filter is bypassed

`data://127.0.0.1/,"\x73\x79\x73\x74\x65\x6d"("\x6c\x73");`

hexadecimal to bypass blacklist (it could also be done with backticks `)

#UNINTENDED

DNS rebinding 

gethostbyname($parsedUrl['host']); is called after @file_get_contents($url, false, $context); 

