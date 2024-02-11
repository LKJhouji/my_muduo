cmake_minimum_required(VERSION 3.0)

project(my_muduo)

aux_source_directory(. SRC_LIST)

add_library(my_muduo SHARED ${SRC_LIST})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_GLIBCXX_USE_CXX11_ABI=0 -fPIC")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

#add_executable(Timestamp ${SRC_LIST})

set_target_properties(my_muduo PROPERTIES OUTPUT_NAME "my_muduo")

