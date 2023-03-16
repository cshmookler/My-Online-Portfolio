cmake_minimum_required(VERSION 3.22.1)
project(csp VERSION 0.0.1)

file(GLOB_RECURSE SOURCES_ ${CMAKE_SOURCE_DIR}/csp/*.cpp)
file(GLOB_RECURSE HEADERS_ ${CMAKE_SOURCE_DIR}/csp/*.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCES_} ${HEADERS_})

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall -Wfloat-conversion)

target_link_libraries(${PROJECT_NAME} ssl crypto)

file(COPY
     ${CMAKE_SOURCE_DIR}/csp/views
     ${CMAKE_SOURCE_DIR}/csp/styles
     ${CMAKE_SOURCE_DIR}/csp/scripts
     ${CMAKE_SOURCE_DIR}/csp/images
     ${CMAKE_SOURCE_DIR}/csp/ssl
     DESTINATION
     ${CMAKE_BINARY_DIR})
