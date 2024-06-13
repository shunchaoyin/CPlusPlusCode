cmake_minimum_required(VERSION 3.10)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(${PROJECT_SOURCE_DIR}/utility SRC)

include_directories(${PROJECT_SOURCE_DIR}/utility)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(logger main.cpp ${SRC})
