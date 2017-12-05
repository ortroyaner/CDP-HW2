cmake_minimum_required(VERSION 3.8)
project(DCP2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        LICENSE
        main.o
        Makefile
        parallel-walsh.c)

add_executable(DCP2 ${SOURCE_FILES})