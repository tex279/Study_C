cmake_minimum_required(VERSION 3.14)
project(gtest)

if (DEBUG)
    add_definitions("-g -O0 -std=c++17 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)


file(GLOB SOURCES src/*.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${BLANKS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BLANKS_LIB_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

SET(memcheck_command)

if (WITH_MEMCHECK)
    message("Memcheck enabled")
    SET(memcheck_command ${CMAKE_SOURCE_DIR}/run_memtest.sh)
else()
    message("Memcheck disabled")
endif()