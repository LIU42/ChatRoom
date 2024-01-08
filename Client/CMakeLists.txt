cmake_minimum_required(VERSION 3.0.0)
project(ChatRoom-Client VERSION 0.1.0 LANGUAGES C CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ChatRoom-Client main.cpp client.cpp)
target_link_libraries(ChatRoom-Client ${CURSES_LIBRARY})
