cmake_minimum_required(VERSION 3.16)
project(WebhookServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/uWebSockets /usr/local/include/uSockets)
link_directories(/usr/local/lib)

find_package(OpenSSL REQUIRED)

add_executable(webhook_server serverWebhook.cpp)

target_link_libraries(webhook_server usockets ssl crypto pthread z)
