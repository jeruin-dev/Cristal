cmake_minimum_required(VERSION 3.15)

project(Cristal LANGUAGES CXX)

set(cmake_export_compile_commands on)

set(Source
       ${CMAKE_CURRENT_SOURCE_DIR}/source/Angel.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/source/triangulo.cpp
)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
add_executable(${PROJECT_NAME} "source/main.cpp" ${add_on})

target_sources(${PROJECT_NAME} PRIVATE "source/Window.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/headers" )
target_link_libraries(${PROJECT_NAME} glfw fmt::fmt glad::glad glm::glm)
