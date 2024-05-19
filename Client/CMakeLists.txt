cmake_minimum_required(VERSION 3.0.0)
project(ChatRoom-Client VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/Headers
    ${CURSES_INCLUDE_DIR}
)

add_executable(ChatRoom-Client 
    "Sources/main.cpp" 
    "Sources/client.cpp"
)

target_link_libraries(ChatRoom-Client ${CURSES_LIBRARY})
