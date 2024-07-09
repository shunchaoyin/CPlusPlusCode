# 定义最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本号
project(Stack VERSION 1.0)
# C++标准
set(CMAKE_CXX_STANDARD 17)

# 设置GoogleTest的路径
set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/../../common/googletest")

set(GTEST_LIB_DIR "${GTEST_ROOT}/lib")
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")

# 查找GoogleTest库和头文件
find_library(GTEST_LIB gtest HINTS ${GTEST_LIB_DIR})
find_library(GTEST_MAIN_LIB gtest_main HINTS ${GTEST_LIB_DIR})
find_path(GTEST_INCLUDE_DIR gtest/gtest.h HINTS ${GTEST_INCLUDE_DIR})

# 包含头文件目录
include_directories(${GTEST_INCLUDE_DIR})


# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加源文件并生成可执行文件
add_executable(${PROJECT_NAME}  Stack_Test.cpp Stack.cpp)

# 链接GoogleTest库
target_link_libraries(${PROJECT_NAME} ${GTEST_LIB} ${GTEST_MAIN_LIB})

# 启用测试
enable_testing()

# 添加测试
add_test(NAME MyTest COMMAND ${PROJECT_NAME})

