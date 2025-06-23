cmake_minimum_required(VERSION 3.16)
project(WebSocketDemo)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/uWebSockets /usr/local/include/uSockets)
link_directories(/usr/local/lib)

find_package(OpenSSL REQUIRED)

add_executable(server server.cpp)

target_link_libraries(server usockets ssl crypto pthread z)
