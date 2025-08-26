cmake_minimum_required(VERSION "3.5.0")
project("ChatRoom" VERSION "0.1.0" "LANGUAGES" "C")

find_package("Threads")

add_executable(
    "ChatRoom"
    "sources/connection.c"
    "sources/main.c"
    "sources/server.c"
)

target_link_libraries("ChatRoom" ${CMAKE_THREAD_LIBS_INIT})
