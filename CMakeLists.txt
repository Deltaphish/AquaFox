cmake_minimum_required(VERSION 2.8)
find_package(glfw3 3.2 REQUIRED)

project(AquaFox)
add_executable(${PROJECT_NAME} "main.cpp" "Input.cpp" "vertex.cpp" "graphic.cpp" "glad.c")
target_link_libraries(${PROJECT_NAME} glfw m dl)
