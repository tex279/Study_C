cmake_minimum_required(VERSION 3.14)
project(blanks_lib)

if (DEBUG)
    add_definitions("-fprofile-arcs -ftest-coverage -fPIC -O0")
endif(DEBUG)

file(GLOB SOURCES blanks_lib/src/blank.c
        blanks_lib/src/list_blanks.c
        blanks_lib/src/utils.c
        blanks_lib/src/list_parts.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/blanks_lib/include)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC blanks_lib/include)

set(BLANKS_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(BLANKS_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
