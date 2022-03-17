cmake_minimum_required(VERSION 3.21)
project(razpoznavalnik_1_Lovro35)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp/src)

add_executable(razpoznavalnik_1_Lovro35
        cpp/src/Main.cpp
        cpp/src/Scanner.h
        cpp/src/task.cpp
        cpp/src/Token.h)
