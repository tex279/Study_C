cmake_minimum_required(VERSION 3.14)
project(generator)

add_definitions("-g -O0 -std=c99 -Wall -Wextra -Werror -Wpedantic")

file(GLOB SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

