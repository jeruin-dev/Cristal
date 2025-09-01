cmake_minimum_required(VERSION 4.0)

project(Cristal LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
add_executable(${PROJECT_NAME} "source/main.cpp")

target_link_libraries(${PROJECT_NAME} glfw fmt::fmt glad::glad)
