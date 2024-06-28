# Faulty Pass
> author: thek0der, category: pwn
### Description
It's April Fools' Day (let's pretend). You want to prank a friend by hacking his server. He has a login portal that only asks for a password. You know the password generator he uses, and you remember his password starts with <b>r#Ndq</b>. He also set this up in February 2024. Break into it! :)
Connection Info: 85.120.206.114:9001

### Server deploy command
```
cd /home/ubuntu/cyberhackday2024/faulty-pass; sudo docker-compose up -d --build
```

### Hints:
- Hint 1: Generate a password lists with all the passwords that can be generated in February 2024

### Flag
<details>
    <summary>Click to reveal flag</summary>
    HCamp{cf9738b889960f321f5eaf25ed7bb878d24934f58cc7a86b446930b980fb492f}
</details>