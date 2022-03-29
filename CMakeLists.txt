cmake_minimum_required(VERSION 3.18.4)
project(Blanks)

option(DEBUG "no release" ON)
option(RELEASE "in production" OFF)

add_subdirectory(project)

message("BLANKS_LIB_INCLUDE_DIRS = ${BLANKS_LIB_INCLUDE_DIRS}")
message("BLANKS_LIB_LIBRARIES = ${BLANKS_LIB_LIBRARIES}")

if (DEBUG)
    set(CMAKE_C_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)

set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} project/main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${BLANKS_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${BLANKS_LIB_LIBRARIES})

add_subdirectory(gtest)
