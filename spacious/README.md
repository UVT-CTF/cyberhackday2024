# Spacious
> author: Andy, category: stegano

### Description

Someone told me to teach you how to connect to this but I'm not sure you'll need it :
Connection : nc 85.120.206.114 12346
### Flag

<details>
  <summary>Click to reveal the flag</summary>
            HCamp{quite_spacious_innit}
</details>

### Deploy

```
cd spacious/private/host ;sudo docker build -t spacious .;sudo docker run -p 12346:12346 spacious
```
