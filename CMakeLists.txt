cmake_minimum_required(VERSION 3.20)

project(aoc2024 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_STANDARD 23)


# find_package(GTest REQUIRED)
# enable_testing()

add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)
add_executable(day3 day3.cpp)
add_executable(day4 day4.cpp)
add_executable(day5 day5.cpp)
add_executable(day6 day6.cpp)
add_executable(day7 day7.cpp)
add_executable(day8 day8.cpp)
add_executable(day9 day9.cpp)
add_executable(day10 day10.cpp)
add_executable(day11 day11.cpp)
add_executable(day12 day12.cpp)
add_executable(day13 day13.cpp)
add_executable(day14 day14.cpp)
add_executable(day15 day15.cpp)
add_executable(day16 day16.cpp)

# target_link_libraries(day1 ${Boost_LIBRARIES})
# target_link_libraries(day2 ${Boost_LIBRARIES})
# target_link_libraries(day3 ${Boost_LIBRARIES})
# target_link_libraries(tests PRIVATE gtest::gtest)

