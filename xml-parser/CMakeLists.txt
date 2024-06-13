cmake_minimum_required(VERSION 3.10)
project(smart_ptr_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(xml)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/xml/*.cpp")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(xml_parser main.cpp ${SRC_LIST})
