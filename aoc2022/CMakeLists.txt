cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

add_executable(day01 day01.cpp)
add_executable(day02 day02.cpp)
add_executable(day03 day03.cpp)
add_executable(day04 day04.cpp)
target_include_directories(day04 PRIVATE "${CMAKE_SOURCE_DIR}")
add_executable(day05 day05.cpp)
add_executable(day06 day06.cpp)
add_executable(day07 day07.cpp)
