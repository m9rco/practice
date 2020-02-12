# 创建文件并写入一些简短的内容

可以使用`cat`带的这个技能来做到

```bash
cat << EOF > /etc/yum.repos.d/google-chrome.repo
[google-chrome]
name=google-chrome
baseurl=http://dl.google.com/linux/chrome/rpm/stable/$basearch
enabled=1
gpgcheck=0
gpgkey=https://dl.google.com/linux/linux_signing_key.pub
EOF
```


# set -e

可以使用 `set -e` 让错误及时退出

```bash
#!/bin/bash

set -e
```
