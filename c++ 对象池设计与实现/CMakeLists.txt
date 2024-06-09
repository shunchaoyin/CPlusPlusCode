cmake_minimum_required(VERSION 3.19)
project(yazi-object)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(test_new test_new/main.cpp)
add_executable(test_new2 test_new2/main.cpp)
add_executable(test_malloc test_malloc/main.cpp)
add_executable(test_array test_array/main.cpp)
add_executable(test_stack test_stack/main.cpp)
add_executable(test_heap test_heap/main.cpp)
add_executable(test_block test_block/main.cpp)
