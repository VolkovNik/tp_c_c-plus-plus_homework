#!/usr/bin/env bash

cppcheck --inconclusive --enable=all --language=c main.c matrix.c matrix.h parallel_column_sum.c parallel_column_sum.h sequential_column_sum.c sequential_column_sum.h test.cpp

# cppcheck --enable=warning,performance,portability,style --language=c matrix.c matrix.h parallel_column_sum.c parallel_column_sum.h sequential_column_sum.c sequential_column_sum.h test.cpp