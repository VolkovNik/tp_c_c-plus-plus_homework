#!/usr/bin/env bash

cppcheck --inconclusive --enable=all --language=c development_task.h development_task.c main.c

# cppcheck --enable=warning,performance,portability,style --language=c evelopment_task.h development_task.c main.c