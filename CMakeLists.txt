cmake_minimum_required(VERSION 3.31)

project(plasma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories("include")

add_executable(plasma src/main.cpp src/diamond.cpp src/square.cpp)

target_link_libraries(plasma OpenGL::GL glfw)