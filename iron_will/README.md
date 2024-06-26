# Iron Will

> author: Andy, category: stegano

### Description

Don't give up. Persevere. Cultivate an iron will. You will need it for this. I have lost a very important document. I need to send to my boss but I don't have the file.
Connection : nc 85.120.206.114 12345 < filename

### Flag

<details>
  <summary>Click to reveal the flag</summary>
            HCamp{this time I am iron, I am power , I am ... RUST}
</details>

### Deploy

```
cd iron_will/private/host ;sudo docker build -t iron_will .;sudo docker run -p 12345:12345 iron_will
```
