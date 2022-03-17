cmake_minimum_required(VERSION 3.0.0)
project(blanks_lib)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES src/blank.c
        src/list_blanks.c
        src/list_parts.c
        src/utils.c)

INCLUDE_DIRECTORIES(include/)

add_library(${PROJECT_NAME} ${SOURCES})

set(BLANKS_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(BLANKS_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

add_subdirectory(gtest)

