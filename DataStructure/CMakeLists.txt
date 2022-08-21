cmake_minimum_required(VERSION 3.20)
project(DataStructure C)

set(CMAKE_C_STANDARD 11)

#
file(GLOB SOURCES
        "Src/*.*"
        "Inc/*.*"
        "Tests/*.*"
        "datastructure.h"
        "main.c"
)

INCLUDE_DIRECTORIES(
        Inc
        Tests
)

add_executable(DataStructure ${SOURCES})

