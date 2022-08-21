cmake_minimum_required(VERSION 3.22)
project(websocket-server C)
set(CMAKE_C_STANDARD 99)

add_subdirectory(src/b64)
#include_directories(http-parser)
add_executable(websocket-server src/main.c src/tcp_epoll.c src/tcp_epoll.h src/tcp_ws.c src/tcp_ws.h src/tcp_session.c src/tcp_session.h src/http-parser/http_parser.c)

#target_include_directories(embedded_final_homework PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/b64")
# 添加ssl库 crypto库 b64c库
target_link_libraries(websocket-server ssl crypto b64c)
