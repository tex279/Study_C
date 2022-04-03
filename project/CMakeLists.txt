cmake_minimum_required(VERSION 3.14)

if (DEBUG)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_FLAGS "-g -lpthread -fprofile-arcs -ftest-coverage -fPIC -O0 -fPIC  -Wall -Wextra -Werror -Wpedantic -lpthread")
    set(CMAKE_C_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)

project(GENERAL)

file(GLOB SOURCES general/src/utils.c
        general/src/format_record_impl.c
        general/src/load_database.c
        general/src/record_impl.c
        general/src/record_sort_impl.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

set(GENERAL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(GENERAL_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


project(IMPERATIVE_MODEL)

file(GLOB SOURCES pattern/imperative_model/src/database_functional_impl.c
        pattern/imperative_model/src/matrix.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/pattern/imperative_model/include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pattern/imperative_model/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

set(IMPERATIVE_MODEL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(IMPERATIVE_MODEL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


project(MULTI_THREADED_MODEL)

file(GLOB SOURCES pattern/multi_threaded_model/src/database_functional_multi_thread_impl.c
        pattern/multi_threaded_model/src/matrix.c)

file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/pattern/multi_threaded_model/include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pattern/multi_threaded_model/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/general/include)

set(MULTI_THREADED_MODEL_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MULTI_THREADED_MODEL_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

