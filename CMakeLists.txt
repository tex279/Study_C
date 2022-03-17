cmake_minimum_required(VERSION 3.0.0)
project(blanks)

OPTION(WITH_MEMCHECK "Run with memcheck" OFF)

INCLUDE_DIRECTORIES(project/include/)

add_subdirectory(project)

message("BLANKS_INCLUDE_DIRS = ${BLANKS_INCLUDE_DIRS}")
message("BLANKS_LIBRARIES = ${BLANKS_LIBRARIES}")

add_executable(${PROJECT_NAME} project/src/main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

target_include_directories(${PROJECT_NAME} PUBLIC ${BLANKS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${BLANKS_LIBRARIES})


ENABLE_TESTING()
