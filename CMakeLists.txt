cmake_minimum_required(VERSION 3.0.0)
project(ChatRoom VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(Client ChatRoom-Client)
add_subdirectory(Server ChatRoom-Server)
