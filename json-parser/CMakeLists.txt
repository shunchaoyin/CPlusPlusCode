cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
project(JSONPASER)
include_directories(json)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 搜索 src 目录下的源文件
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/json/*.cpp)
add_executable(json_parser  main.cpp ${MAIN_SRC})



