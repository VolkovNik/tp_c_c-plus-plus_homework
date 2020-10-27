cmake_minimum_required(VERSION 3.9)
project(tp_c_cpp_homework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -pedantic -fPIC -g")

add_library(sequential STATIC sequential_column_sum.c)
add_library(parallel SHARED parallel_column_sum.c matrix.c)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(gtest tests.cpp)
target_link_libraries(gtest ${GTEST_LIBRARIES} sequential parallel)

add_executable(tp_c_cpp_homework main.c matrix.h matrix.c)
target_link_libraries(tp_c_cpp_homework sequential)
target_link_libraries(tp_c_cpp_homework parallel)