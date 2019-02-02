# 图书管理系统 BookManageSystem

![](https://img.shields.io/badge/license-Apache2.0-253bd8.svg)
![](https://img.shields.io/badge/author-dybl-ff69b4.svg)
![](https://img.shields.io/badge/upload-pass-0f9d58.svg)

`lms => Library Managememt System`
(即`图书馆管理系统`)

### 简介:
lms是一个简单的图书馆管理系统，界面是基于qt开发的，用mysql存储数据，基本实现了用户登录注册，增删改查图书及用户等功能，

### 开发环境:
- windows： 1803 64bit
- macosx 10.13.3 64bit
- Qt: 5.11.2
- MySQL: 5.7.24


### For MacOSX

> 在release里下载`lms.dmg`,自行选择合适的安装位置，本程序大概占用60mb的磁盘空间.

### 使用前配置:

- 确保你本机上已经安装了MySQL，并且版本号5.5.x以后，截至目前最新的是5.7.24，当然你用5.0.x也许也能够运行，不过我没有测试过。

**注意，不要使用版本号为8.x.x的，版本号前缀不是5系列的不兼容本程序**

- 没有安装的可以在mysql官网上免费下载最新的5.7.24-windows-社区版，32位或者64位的都行.如有疑惑，请自行百度

### 数据库脚本导入:

- 已经为mysql配置过环境变量的直接打开cmd或者powershell，输入以下命令即可

``` bash
mysql -uroot -p 
create database library;
use library;
source <libsys安装目录>\doc\bak.sql
```
**导入过程出现问题，请根据报错自行排查**


## License

```sh
Copyright 2019 dybl

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
