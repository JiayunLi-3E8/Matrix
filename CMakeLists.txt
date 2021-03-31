cmake_minimum_required(VERSION 3.0.0)
project(Matrix)

include_directories(./include)

file(GLOB SRC_FILE ./source/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILE})
