add_executable(${PROJECT_NAME}
        main.cpp
        bloomApp.h
        bloomApp.cpp
        openGL/shader.cpp
        openGL/shader.h
        filesystem/fileReader.cpp
        filesystem/fileReader.h
        window/window.h
        window/openGlWindow.cpp
        window/openGlWindow.h
)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        $<IF:$<TARGET_EXISTS:glm::glm>,glm::glm,glm>
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        volk::volk
        glad
)