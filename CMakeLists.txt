cmake_minimum_required(VERSION 3.17)
project(CSCI2312_A2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(include)

add_executable(Grids src/main.cpp src/BitGrid.cpp include/BitGrid.h src/Point.cpp include/Point.h src/Bitset.cpp include/Bitset.h)
