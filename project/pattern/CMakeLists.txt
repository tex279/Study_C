cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal ")


if (DEBUG)
    add_definitions("-fprofile-arcs -ftest-coverage -fPIC -O0")
endif(DEBUG)

file(GLOB SOURCES imperative_model/src/*.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/blanks_lib/include)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC blanks_lib/include)
