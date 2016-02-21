cmake_minimum_required(VERSION 2.8)

project(hart_serial)

include_directories(include)
include_directories(thirdparty/Catch/single_include/)

file(GLOB_RECURSE sources src/hart/*.cpp)
file(GLOB_RECURSE test_sources test/*.cpp)

message(sources)
message(test_sources)

add_executable(hart_serial_tests ${test_sources})


