cmake_minimum_required(VERSION 3.14)
project(generator)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal ")

file(GLOB SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

