cmake_minimum_required(VERSION 4.0)

project(Cristal LANGUAGES CXX)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} "source/main.cpp")

target_link_libraries(${PROJECT_NAME} fmt::fmt)
