cmake_minimum_required(VERSION 3.9)
project(tp_c_cpp_homework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_executable(tp_c_cpp_homework main.c matrix.h matrix.c)