cmake_minimum_required(VERSION 3.0)
project(my_muduo)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) # 库生成路径
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11") # 编译类型

aux_source_directory(. SRC_LIST) # 源文件路径
add_library(my_muduo SHARED ${SRC_LIST}) # 生成动态库


