cmake_minimum_required(VERSION 3.10.0)
project(BRAINLESS VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(GRAPIXY_SOURCES
Grapixy/window.c
Grapixy/window.h
Grapixy/Dependencies/glad.c
Grapixy/Dependencies/glad.h
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)

add_executable(BRAINLESS src/main.cpp ${GRAPIXY_SOURCES})
target_link_libraries(BRAINLESS glfw OpenGL::GL)
include(CTest)
enable_testing()

