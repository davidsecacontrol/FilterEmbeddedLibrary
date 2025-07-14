cmake_minimum_required(VERSION 4.0)

project(FILTER_LIBRARY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add warnings depending on the compiler
if(MSVC)
    # Use MSVC-compatible warning flags
    add_compile_options(/W4 /permissive-)
else()
    # Use GCC/Clang-style flags
    add_compile_options(-Wall -Wextra -Wimplicit -Wundef -Wimplicit-fallthrough)
endif()


add_executable(example1_Moving_average examples/example1_Moving_average.cpp)
add_executable(example2_Exponentially_Weighted_Moving_Average examples/example2_Exponentially_Weighted_Moving_Average.cpp)

target_include_directories(example1_Moving_average PRIVATE include)
target_include_directories(example2_Exponentially_Weighted_Moving_Average PRIVATE include)
