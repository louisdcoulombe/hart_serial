cmake_minimum_required(VERSION 2.8)

project(hart_serial CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wextra")

include_directories(include)
include_directories(thirdparty/Catch/single_include/)

file(GLOB_RECURSE sources src/hart/*.cpp)
file(GLOB_RECURSE test_sources test/*.cpp)

message(STATUS ${sources})
message(STATUS ${test_sources})

add_executable(hart_serial_tests ${sources} ${test_sources})


