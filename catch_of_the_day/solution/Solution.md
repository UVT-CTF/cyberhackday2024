We have `flag.png` that won't open. If we inspect it in a Hexeditor, we can see that the header contains extra bytes before the actual `png` header. We can remove this in a Hexeditor or using a Python script similar to the one in this directory. 

After we remove the excess bytes, we get a picture of a red herring, that hints to look inside the file for other secrets. We can do this by using `binwalk` with the corresponding flag `-e` to actually extract the embedded secret:
```
binwalk -e flag.png
```

We have now extracted another file: `actual_flag.png` When we open it, it hints to look at the details. We can look  in the metadata of this second file using `exiftool`:
```
exiftool actual_flag.png
```

The flag is there, as a comment:
```
Comment: HCamp{dec4b9362ddcccb4154e4a5b0506c870}
```
