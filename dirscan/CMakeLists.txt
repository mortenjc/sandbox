cmake_minimum_required(VERSION 3.10)
include_directories(.)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")

set(INCLUDE DirScan.h CLI11.hpp Album.h)
set(SOURCE main.cpp DirScan.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} --std=c++11")

add_executable(dirscan ${INCLUDE} ${SOURCE})
