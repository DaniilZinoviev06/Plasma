cmake_minimum_required(VERSION 3.31)

project(plasma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB CPP "src/*.cpp")

include_directories("include")

add_executable(plasma ${CPP})