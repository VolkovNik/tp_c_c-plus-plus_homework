cmake_minimum_required(VERSION 3.17)
project(tp_c_cpp_homework C)

set(CMAKE_C 11)
set(CMAKE_C_CPPCHECK "cppcheck")

find_program(CMAKE_C_CPPCHECK NAMES cppcheck)
if (CMAKE_C_CPPCHECK)
    list(
            APPEND CMAKE_C_CPPCHECK
            "--enable=performance,portability,warning,style"
    )
endif()

add_executable(tp_c_cpp_homework main.c development_task.h development_task.c)