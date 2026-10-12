cmake_minimum_required(VERSION 3.10)
project(Problem124)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

add_executable(code code.cpp)