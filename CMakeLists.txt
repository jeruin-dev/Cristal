cmake_minimum_required(VERSION 3.15)

project(Cristal LANGUAGES CXX)

set(cmake_export_compile_commands on)


add_subdirectory(submodules/AngelEngine)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
add_executable(${PROJECT_NAME} "source/main.cpp")

target_sources(${PROJECT_NAME} PRIVATE "source/Cristal.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/headers")
target_link_libraries(${PROJECT_NAME} glfw fmt::fmt glad::glad AngelEngine glm::glm)
