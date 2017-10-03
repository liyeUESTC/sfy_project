project(forward)

cmake_minimum_required(VERSION 2.8)

aux_source_directory(server SERVER_DIR)
aux_source_directory(client CLIENT_DIR)

include_directories(common .)

add_subdirectory(common)

set(CMAKE_CXX_FLAGS " -std=c++11")

add_executable(Server ${SERVER_DIR})
add_executable(Client ${CLIENT_DIR})

target_link_libraries(Server BaseClass)
target_link_libraries(Client BaseClass)

set(EXECUTABLE_OUTPUT_PATH ../bin)
