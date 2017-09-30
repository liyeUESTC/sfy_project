project(test)

cmake_minimum_required(VERSION 2.8)

aux_source_directory(test TEST_DIR)

include_directories(common .)

add_subdirectory(common)

set(CMAKE_CXX_FLAGS "-g -std=c++11")

add_executable(graduation_main ${TEST_DIR})

target_link_libraries(graduation_main  BaseClass)

set(EXECUTABLE_OUTPUT_PATH ../bin)
