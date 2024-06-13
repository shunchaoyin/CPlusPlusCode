cmake_minimum_required(VERSION 3.10)
project(app)
set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/serialize)

set(execute_output_path ${PROJECT_SOURCE_DIR}/bin)
file(GLOB_RECURSE serialize_SRC  "serialize/*.cpp")
add_executable(serialize main.cpp ${serialize_SRC})