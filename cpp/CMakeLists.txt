cmake_minimum_required(VERSION 3.13)
project(razpoznavalnik-1-Lovro35)

add_executable(razpoznavalnik-1-Lovro35 src/task.cpp src/Scanner.h src/Token.h)
set_property(TARGET razpoznavalnik-1-Lovro35 PROPERTY CXX_STANDARD 20)
