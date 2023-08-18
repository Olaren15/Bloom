add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glm
        SDL2::SDL2main
        SDL2::SDL2
        volk::volk
)