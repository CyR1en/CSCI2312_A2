cmake_minimum_required(VERSION 3.17)
project(CSCI2312_A2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Grids src/main.cpp src/BitGrid.cpp src/BitGrid.h src/Point.cpp src/Point.h src/Bitset.cpp src/Bitset.h)
