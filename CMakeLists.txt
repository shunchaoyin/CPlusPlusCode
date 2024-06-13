cmake_minimum_required(VERSION 3.0)
project(Study)

set(CMAKE_CXX_STANDARD 17)

# 可执行程序的名字
set(LOGGER CPluslog)
set(JSON_PARSER json-parser)
#set(REFLECT reflect)
# 添加子目录


add_subdirectory(CPluslog)
add_subdirectory(json-parser)
add_subdirectory(reflect)
add_subdirectory(serialize)
add_subdirectory(singleton)
add_subdirectory(xml-parser)