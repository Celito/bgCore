cmake_minimum_required(VERSION 3.2)
project(bgCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(bgCore ${SOURCE_FILES} Player.cpp Player.h GameManager.cpp GameManager.h)