cmake_minimum_required(VERSION 3.10)
include_directories(.)
set(INCLUDE DirScan.h)
set(SOURCE main.cpp DirScan.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(dirscan ${INCLUDE} ${SOURCE})
