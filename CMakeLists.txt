cmake_minimum_required(VERSION 4.1.0)

project(FILTER_LIBRARY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(example1_Moving_average examples/example1_Moving_average.cpp)

target_include_directories(example1_Moving_average PRIVATE include)
