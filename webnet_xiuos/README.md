# WebNet_XiUOS

## 介绍

此项目是基于Rt-Thread团队的**WebNet** 项目移植，由于XiUOS和RT-Thread开发的WebNet协议不兼容，所以单独建仓。该软件包基于 HTTP 协议实现了Web服务器，且支持多种模块功能的扩展，占用资源少，对于硬件资源有限的嵌入式RTOS来说，非常适合。

WebNet 软件包功能特点如下：

- 支持 HTTP 1.0/1.1
- 支持 AUTH 基本认证功能
- 支持 CGI 功能
- 支持 ASP 变量替换功能
- 支持 SSI 文件嵌入功能
- 支持 INDEX 目录文件显示功能
- 支持 ALIAS 别名访问功能
- 支持文件上传功能
- 支持预压缩功能
- 支持缓存功能
- 支持断点续传功能

## 目录结构

| 名称       | 说明                         |
| ---------- | ---------------------------- |
| inc        | 头文件目录                   |
| src        | 源文件目录                   |
| module     | 功能模块文件目录             |
| samples    | 示例文件目录                 |
| README.md  | 软件包使用说明               |
| SConscript | RT-Thread **默认的构建脚本** |

## 使用

该软件包作为子模块已经归入XiUOS主仓，在主仓更目录执行以下命令

```
git submodule update APP_Framework/Applications/webnet/WebNet_XiUOS
```

### 示例程序的使用

WebNet 软件包提供了一个综合的示例页面用于展示软件包的多项功能，包括：AUTH、CGI、ASP、SSI、INDEX、ALIAS、Upload 等功能

静态页面需要上传到文件系统中服务器根目录下（示例中使用根目录为 /webnet）。设备挂载文件系统成功，需要依次执行下面操作：

1. 使用 `mkdir webnet` 命令创建 WebNet 软件包根目录 **/webnet**，并使用 `cd webnet` 命令进入该目录；

2. 使用 `mkdir admin` 和 `mkdir upload` 命令创建 **/webnet/admin** 和 **/webnet/upload** ，用于 AUTH 功能和 Upload 功能测试；

3. 将 WebNet 软件包 /sample 目录下的：**index.html**、**index.shtml**、**version.asp** 三个文件依次上传到设备 **/webnet** 目录（WebNet 根目录）中（可以使用 TFTP 工具上传文件)

创建目录和上传文件成功之后，就可以启动例程，测试 WebNet 软件功能。

本例程参数和环境配置如下：

- 监听端口号：80

- 根目录地址：/webnet

- 文件系统：FAT 文件系统

设备启动，连接网络成功之后，在 Shell 命令行输入 `webnet_test` 命令启动 WebNet 服务器。查看 Shell 命令行，显示如下日志信息，说明 WebNet 服务器初始化成功：

```c
msh />webnet_test
[I/wn] RT-Thread webnet package (V2.0.0) initialize success.
```

然后在 Shell 命令行中使用 `ifconfig` 命令获取本设备 IP地址为 **192.168.12.29**。

```c
msh />ifconfig
network interface: w0 (Default)
MTU: 1500
MAC: 44 32 c4 75 e0 59 
FLAGS: UP LINK_UP ETHARP BROADCAST IGMP
ip address: 192.168.12.29
gw address: 192.168.10.1
net mask  : 255.255.0.0
dns server #0: 192.168.10.1
dns server #1: 223.5.5.5
```

接着在浏览器（这里使用谷歌浏览器）中输入设备 IP 地址，将默认访问设备根目录下 **/index.html** 文件,这时浏览器会有相应页面展示。

## 注意

WebNet 软件包使用需要文件系统和Lwip协议栈的支持。

webnet.c 文件中注意以下定义，注意其他操作系统lwip协议栈的大小设置

```
#ifdef  ADD_XIZI_FETURES
#if defined(RT_USING_LWIP) && (RT_LWIP_TCPTHREAD_STACKSIZE < 1408)
#error The lwIP tcpip thread stack size(RT_LWIP_TCPTHREAD_STACKSIZE) must more than 1408
#endif
#endif
```

webnet文件夹为该分支的一个前端页面文件版本
