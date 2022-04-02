cmake_minimum_required(VERSION 3.18.4)
project(HW-2)

add_subdirectory(project)

option(DEBUG "no release" ON)
option(RELEASE "in production" OFF)

message("IMPERATIVE_MODEL_INCLUDE_DIRS = ${IMPERATIVE_MODEL_INCLUDE_DIRS}")
message("IMPERATIVE_MODEL_LIB_LIBRARIES = ${IMPERATIVE_MODEL_LIB_LIBRARIES}")

message("GENERAL_LIB_INCLUDE_DIRS = ${GENERAL_LIB_INCLUDE_DIRS}")
message("GENERAL_LIB_LIBRARIES = ${GENERAL_LIB_LIBRARIES}")

if (DEBUG)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_FLAGS "-g -fprofile-arcs -ftest-coverage -fPIC -O0 -fPIC  -Wall -Wextra -Werror -Wpedantic")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)


file(GLOB SOURCES project/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GENERAL_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GENERAL_LIB_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${IMPERATIVE_MODEL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IMPERATIVE_MODEL_LIB_LIBRARIES})

add_subdirectory(generator_data)
add_subdirectory(gtest)
