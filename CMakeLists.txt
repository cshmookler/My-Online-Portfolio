cmake_minimum_required(VERSION 3.22.1)
project(csp VERSION 0.0.1)

file(GLOB_RECURSE SOURCES_ ${CMAKE_SOURCE_DIR}/csp/*.cpp)
file(GLOB_RECURSE HEADERS_ ${CMAKE_SOURCE_DIR}/csp/*.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/csp)

add_executable(${PROJECT_NAME} ${SOURCES_} ${HEADERS_})

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall -Wfloat-conversion)

target_link_libraries(${PROJECT_NAME} ssl crypto)