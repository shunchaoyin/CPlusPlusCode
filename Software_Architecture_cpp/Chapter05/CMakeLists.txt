cmake_minimum_required(VERSION 3.31)

project(chapter05)
set(CMAKE_CXX_STANDARD 20)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 查找 GSL 库
find_package(GSL REQUIRED)

# 包含 GSL 头文件路径
include_directories(${GSL_INCLUDE_DIRS})

# 添加可执行文件
add_executable(base 1_base.cpp)

# 链接 GSL 库
target_link_libraries(base GSL::gsl GSL::gslcblas)
target_compile_features(base PRIVATE cxx_std_20)
target_compile_options(base PRIVATE ${BASE_COMPILE_FLAGS})


add_executable(range2 2_range.cpp)
# 链接 GSL 库
target_link_libraries(range2 GSL::gsl GSL::gslcblas)
target_compile_features(range2 PRIVATE cxx_std_20)
target_compile_options(range2 PRIVATE ${BASE_COMPILE_FLAGS})