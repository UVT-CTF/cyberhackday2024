# Special data
> author: Paul  category: Web
### Description
My friend made a website to debug code, he thought that he will be able to debug only files from his server, but boy, was he wrong
### Flag
<details>
  <summary>Click to reveal the flag</summary>
HCamp{d3dad30ff73f76a60a59548e118e3027256c582e3731a98d229b4b502cc07e68}
</details>

### Deploy
```
cd "/home/ubuntu/cyberhackday2024/special_data/private"
docker build -t my-php-app . && docker run -d -p 6666:80 --name my-php-app-container my-php-app
```
