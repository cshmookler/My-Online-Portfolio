cmake_minimum_required(VERSION 3.22.1)
project(cs-server VERSION 0.0.1)

file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/cs-server/*.cpp)
file(GLOB_RECURSE HDRS ${CMAKE_SOURCE_DIR}/cs-server/*.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME} ssl crypto)

file(COPY
     ${CMAKE_SOURCE_DIR}/cs-server/views
     ${CMAKE_SOURCE_DIR}/cs-server/styles
     ${CMAKE_SOURCE_DIR}/cs-server/scripts
     DESTINATION
     ${CMAKE_BINARY_DIR})
