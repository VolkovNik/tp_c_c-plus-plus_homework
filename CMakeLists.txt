cmake_minimum_required(VERSION 3.17)
project(tp_c_cpp_homework C)

set(CMAKE_CXX 11)
set(CMAKE_CXX_CPPCHECK "cppcheck")

add_executable(tp_c_cpp_homework main.c development_task.h development_task.c)