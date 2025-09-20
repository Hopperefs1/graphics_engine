cmake_minimum_required(VERSION 3.10.0)
project(BRAINLESS VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(BRAINLESS 
src/main.cpp
src/glad.h
src/glad.c)

target_link_libraries(BRAINLESS glfw OpenGL::GL)
include(CTest)
enable_testing()

