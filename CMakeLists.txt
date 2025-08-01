cmake_minimum_required(VERSION 4.0)

project(FILTER_LIBRARY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add warnings depending on the compiler ---------------------------------------------------------
if(MSVC)
    # Use MSVC-compatible warning flags
    add_compile_options(/W4 /permissive-)
else()
    # Use GCC/Clang-style flags
    add_compile_options(-Wall -Wextra -Wimplicit -Wundef -Wimplicit-fallthrough)
endif()

# Add google tests ------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)


# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Adding tests
enable_testing()

add_executable(Filter_test_compilation tests/Filter_testing.cc)
target_link_libraries(Filter_test_compilation GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Filter_test_compilation)

# ----------------------------------------------------------------------------------------------

add_executable(example1_Moving_average examples/example1_Moving_average.cpp)
add_executable(example2_Exponentially_Weighted_Moving_Average examples/example2_Exponentially_Weighted_Moving_Average.cpp)

target_include_directories(example1_Moving_average PRIVATE include)
target_include_directories(example2_Exponentially_Weighted_Moving_Average PRIVATE include)
