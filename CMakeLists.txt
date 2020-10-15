cmake_minimum_required(VERSION 3.9)
project(tp_c_cpp_homework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -Werror -fPIC -g -fprofile-arcs -ftest-coverage")
set(LDFLAGS "${LDFLAGS} -fprofile-arcs -ftest-coverage")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(gtest_develop tests_development_task.cpp)
target_link_libraries(gtest_develop ${GTEST_LIBRARIES})

add_executable(tp_c_cpp_homework main.c development_task.h development_task.c)