cmake_minimum_required(VERSION 3.20)
project(Blanks)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal ")

set(SOURCES project/blanks_lib/src/blank.c
        project/blanks_lib/src/list_blanks.c
        project/blanks_lib/src/list_parts.c
        project/blanks_lib/src/utils.c)

add_library(lib ${SOURCES})
target_include_directories(lib PUBLIC project/blanks_lib/include)

add_executable(main project/main.c)
target_link_libraries(main lib)

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_executable(test.out project/gtest/src/test_blanks.cpp)
target_link_libraries(test.out lib ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

SET (TEST_COMMAND ${memcheck_command} ${CMAKE_BINARY_DIR}/project/tests/tests)
