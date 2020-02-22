# PHP

PHP是一种跨平台[开源](https://github.com/php/php-src)语言，也是目前最流行的web开发语言，本篇用于记录学习及从编程语言本身实现上了解学习PHP


```shell
# 1. 下载源代码并解压
wget https://github.com/php/php-src/archive/php-7.4.3.tar.gz
tar -zxvf php-7.4.3.tar.gz
# 2. 创建一个docker环境用于之后xuexi 
docker run -itd --privileged --name php-src -v $PWD:/root  centos:7  /usr/sbin/init
docker exec -it php-src /bin/bash
# 3. 构建源码编译环境
set -ex \
  && curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo \
  && yum makecache \
  && yum install -y make cmake gcc gcc-c++ autoconf automake libpng-devel libjpeg-devel zlib libxml2-devel ncurses-devel bison libtool-ltdl-devel libiconv libmcrypt mhash mcrypt pcre-devel openssl-devel freetype-devel libcurl-devel
# 4. 编译源码
set -ex  \
  && cd /root \
  && ./configure --prefix=/root/php-7 --enable-fpm \
  && make && make install
```


## 执行原理概述

## 内核架构

## 生命周期

## 内存管理

## 垃圾回收

## 词法与语法分析

## Zend 虚拟机
