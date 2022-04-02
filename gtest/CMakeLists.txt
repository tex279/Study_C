cmake_minimum_required(VERSION 3.14)
project(gtest_general)

if (DEBUG)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)


file(GLOB SOURCES general.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GENERAL_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GENERAL_LIB_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
