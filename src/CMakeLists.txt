add_executable(${PROJECT_NAME}
        main.cpp
        openGlApp.h
        openGlApp.cpp
        openGL/material/shader.cpp
        openGL/material/shader.h
        filesystem/fileReader.cpp
        filesystem/fileReader.h
        window/window.h
        window/openGlWindow.cpp
        window/openGlWindow.h
        openGL/renderer.cpp
        openGL/renderer.h
        window/windowSize.h
        openGL/material/material.h
        openGL/texture.cpp
        openGL/texture.h
        openGL/material/bufferInput.h
        openGL/material/shaderInputFormat.h
        openGL/material/textureInput.h
)

if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
endif(MSVC)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        $<IF:$<TARGET_EXISTS:glm::glm>,glm::glm,glm>
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        glad
        stb
)