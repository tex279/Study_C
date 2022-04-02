cmake_minimum_required(VERSION 3.14)
project(GENERAL)

if (DEBUG)
    add_definitions("-fprofile-arcs -ftest-coverage -fPIC -O0")
endif(DEBUG)

file(GLOB SOURCES general/src/utils.c
        general/src/format_record_impl.c
        general/src/load_database.c
        general/src/record_impl.c
        general/src/record_sort_impl.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

set(GENERAL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(GENERAL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


project(IMPERATIVE_MODEL)

if (DEBUG)
    add_definitions("-fprofile-arcs -ftest-coverage -fPIC -O0")
endif(DEBUG)

file(GLOB SOURCES pattern/imperative_model/src/database_functional_impl.c
        pattern/imperative_model/src/matrix.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/pattern/imperative_model/include)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pattern/imperative_model/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

set(IMPERATIVE_MODEL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(IMPERATIVE_MODEL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

