#pragma once

#include <glad/glad.h>

#include "shader.h"
#include "../window/openGlWindow.h"
#include "material.h"

namespace bloom::openGL {

    class Renderer {
      public:
        explicit Renderer(window::OpenGlWindow& window);
        Renderer(const Renderer&) = delete;
        ~Renderer();

        void drawFrame();

      private:
        window::OpenGlWindow& window;
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint ebo = 0;
        Shader shader;
    };

} // namespace bloom::openGL
