cmake_minimum_required(VERSION 3.5.0)
project(ChatRoom-Server VERSION 0.1.0 LANGUAGES C)

find_package(Threads)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(ChatRoom-Server 
    "src/main.c"
    "src/server.c"
    "src/connection.c"
)

target_link_libraries(ChatRoom-Server ${CMAKE_THREAD_LIBS_INIT})
