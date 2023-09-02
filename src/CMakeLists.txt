add_executable(${PROJECT_NAME}
        main.cpp
        openGlApp.hpp
        openGlApp.cpp
        openGL/shader.cpp
        openGL/shader.hpp
        filesystem/fileReader.cpp
        filesystem/fileReader.hpp
        window/window.hpp
        window/impl/openGlWindow.cpp
        window/impl/openGlWindow.hpp
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
        glad
        stb
)