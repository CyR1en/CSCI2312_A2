cmake_minimum_required(VERSION 3.17)
project(Grids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Grids src/main.cpp src/BitGrid.cpp src/BitGrid.h src/Point.cpp src/Point.h src/Bitset.cpp src/Bitset.h)