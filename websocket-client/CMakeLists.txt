cmake_minimum_required(VERSION 3.22)
project(websocket-client VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

add_executable(websocket-client src/example-client.cpp src/easywsclient.cpp src/easywsclient.hpp)
