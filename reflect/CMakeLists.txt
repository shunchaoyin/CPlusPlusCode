cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD  11)
project(REFLECT)

include_directories(reflect)
include_directories(test)
include_directories(utility)

file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/reflect/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(reflect main.cpp ${SRC_LIST})

