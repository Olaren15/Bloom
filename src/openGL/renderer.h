#pragma once

#include "../window/openGlWindow.h"
#include "material/material.h"
#include "material/shader.h"
#include "texture.h"

#include <glad/glad.h>

namespace bloom::openGL {

    class Renderer {
      public:
        explicit Renderer(window::OpenGlWindow& window);
        Renderer(const Renderer&) = delete;
        ~Renderer();

        void drawFrame() const;

      private:
        window::OpenGlWindow& window;
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint ebo = 0;

        material::Shader shader;
        Texture rem;
        Texture tramway;
        material::Material defaultMaterial;};

} // namespace bloom::openGL
