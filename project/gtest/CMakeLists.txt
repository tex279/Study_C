cmake_minimum_required(VERSION 3.0.0)
project(test_blanks)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

file(GLOB SOURCES *.cpp)

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${BLANKS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BLANKS_LIBRARIES} GTest::gtest_main)
