cmake_minimum_required(VERSION 3.17)
project(tp_c_cpp_homework C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CPPCHECK "cppcheck")

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=performance,portability,warning,style"
    )
endif()

add_executable(tp_c_cpp_homework main.c development_task.h development_task.c)