cmake_minimum_required(VERSION 3.14)
project(GENERAL)

if (DEBUG)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage -fPIC  -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage -fPIC  -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
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
set(GENERAL_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


project(IMPERATIVE_MODEL)

if (DEBUG)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_C_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wpedantic -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
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

