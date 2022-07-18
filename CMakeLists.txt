cmake_minimum_required(VERSION 3.0.0)
project(Matrix VERSION 0.1.0)

file(GLOB SRC_FILE ./source/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_FILE})