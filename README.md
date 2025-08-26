# ChatRoom 聊天室

*<u>v2.0.0 新变化：使用 C 语言重新实现服务端部分，并基于 .NET WinForms 构建图形化客户端界面。</u>*

## 项目简介

基于 TCP Socket 的多线程聊天室，服务端为每个客户端创建一个线程用于维持连接和通信。客户端通过一个独立的线程实时接收消息。

## 使用说明

服务端程序使用 [CMake](https://cmake.org/) 构建，在 Linux 环境中编译运行。

```shell-session
cmake . -D CMAKE_BUILD_TYPE=RELEASE -G "Unix Makefile" 
```

客户端程序使用 [Visual Studio](https://visualstudio.microsoft.com/) 编译运行。
