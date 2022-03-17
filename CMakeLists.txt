cmake_minimum_required(VERSION 3.20)
project(HW-1)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage")

set(CMAKE_C_FLAGS "-g -O0 -Wextra -Werror -g -std=gnu99 -Wall
	-Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond
	-Wfloat-equal -Wlogical-op -Wredundant-decls -Wsign-conversion")

set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_library(lib STATIC
        project/src/blank.c
        project/src/list_blanks.c
        project/src/list_parts.c
        project/src/main.c
        project/src/utils.c)

target_include_directories(lib PUBLIC include)

add_executable(main.out src/main.c)
target_link_libraries(main.out lib)

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(test.out tests/gtest.cpp)
target_link_libraries(test.out lib ${GTEST_LIBRARIES} Threads::Threads)
