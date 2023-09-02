cmake_minimum_required(VERSION 3.0)
project(stb)

add_library(stb src/stb_image.c)
target_include_directories(stb PUBLIC ${Stb_INCLUDE_DIR})
