# Bad Comparison
> author: Paul, category: web
### Description
Something is wrong with our login system, can you find what's wrong and login?
### Flag
<details>
  <summary>Click to reveal the flag</summary>
HCamp{b3255a66ffbb5f996b62e907c857f0609c95a1eabb9762c9b3ca52899b181682}
</details>

Deploy
```
cd "/home/ubuntu/cyberhackday2024/bad_comparison/private"
docker build -t bad_comparison . && docker run -d -p 6689:80 bad_comparison
```
