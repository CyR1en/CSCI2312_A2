cmake_minimum_required(VERSION 3.17)
project(CSCI2312_A2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CSCI2312_A2
    src/BitGrid.cpp
    src/BitGrid.h
    src/Bitset.cpp
    src/Bitset.h
    src/main.cpp
    src/Point.cpp
    src/Point.h)
