cmake_minimum_required(VERSION 3.0.0)
project(ChatRoom-Server VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${PROJECT_SOURCE_DIR}/Headers
)

add_executable(ChatRoom-Server
    "Sources/main.cpp"
    "Sources/server.cpp"
)
