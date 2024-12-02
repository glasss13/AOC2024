cmake_minimum_required(VERSION 3.20)

project(aoc2024 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_STANDARD 23)


# find_package(GTest REQUIRED)
# enable_testing()

add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)


# target_link_libraries(tests PRIVATE gtest::gtest)

