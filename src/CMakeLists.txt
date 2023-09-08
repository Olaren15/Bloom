add_executable(${PROJECT_NAME}
        main.cpp
        openGlApp.hpp
        openGlApp.cpp
        openGL/shader.cpp
        openGL/shader.hpp
        filesystem/fileReader.cpp
        filesystem/fileReader.hpp
        window/window.hpp
        window/impl/sdl2OpenGLWindow.cpp
        window/impl/sdl2OpenGLWindow.hpp
        openGL/renderer.cpp
        openGL/renderer.hpp
        window/windowSize.hpp
        openGL/texture.cpp
        openGL/texture.hpp
        openGL/model/model.hpp
        openGL/model/vertex.hpp
        openGL/model/mesh.hpp
        openGL/model/mesh.cpp
        openGL/model/modelImporter.hpp
        openGL/model/modelImporter.cpp
        ui/uiRenderer.hpp
        ui/backends/inputBackend.hpp
        ui/backends/inputBackend.hpp
        ui/backends/impl/sdl2OpenGLInputBackend.cpp
        ui/backends/impl/sdl2OpenGLInputBackend.hpp
        ui/UiRenderer.cpp
        ui/backends/renderingBackend.hpp
        ui/backends/impl/openGlRenderingBackend.cpp
        ui/backends/impl/openGlRenderingBackend.hpp
        ui/backends/platformBackend.hpp
        ui/uiRendererFactory.cpp
        ui/uiRendererFactory.hpp
        window/backends.hpp
        rendering/backends.hpp
)

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
endif ()

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        glad::glad
        glm::glm
        stb
        assimp::assimp
        imgui::imgui
        unofficial::nativefiledialog::nfd
)