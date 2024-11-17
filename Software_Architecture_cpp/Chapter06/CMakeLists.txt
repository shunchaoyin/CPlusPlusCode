cmake_minimum_required(VERSION 3.15)

project(chapter06)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 查找 GSL 库
find_package(GSL REQUIRED)

# 包含 GSL 头文件路径
include_directories(${GSL_INCLUDE_DIRS})

# 添加可执行文件
add_executable(01_raii 01_raii_gurads.cpp)
add_executable(02_copy_move 02_copy_move.cpp)
add_executable(03_rules_of_5_and_0  03_rules_of_5_and_0.cpp)
add_executable(04_hidden_friend_copy_and_swap 04_hidden_friend_copy_and_swap.cpp)
add_executable(06_policy_based_design 06_policy_based_design.cpp)
# 链接 GSL 库
target_link_libraries(GSL::gsl)