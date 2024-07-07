# 定义最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本号
project(Array VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
# 头文件
include_directories(include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 引入FetchContent模块
include(FetchContent)

# 声明GoogleTest
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG main
)

# 强制使用共享C运行时库
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 拉取并编译GoogleTest
FetchContent_MakeAvailable(GoogleTest)

# 添加源文件
add_executable(${PROJECT_NAME} Test.cpp Array.cpp)

# 链接GoogleTest到项目
target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

# 包含GoogleTest头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ${googletest_SOURCE_DIR}/include ${googletest_BINARY_DIR})

# 启用测试
enable_testing()

# 添加测试
add_test(NAME MyTest COMMAND ${PROJECT_NAME})

