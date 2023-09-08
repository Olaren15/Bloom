cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJECT_NAME Bloom)

project(${PROJECT_NAME} VERSION 1.0.0)

find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(external)
