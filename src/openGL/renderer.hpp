#pragma once

#include "../window/impl/openGlWindow.hpp"
#include "model/model.hpp"
#include "shader.hpp"

namespace bloom::openGL {

    class Renderer {
      public:
        Renderer() = delete;
        explicit Renderer(window::OpenGlWindow* window);
        void updateMatrices() const;
        Renderer(const Renderer&) = delete;
        Renderer(const Renderer&&) = delete;
        ~Renderer() = default;

        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(const Renderer&&) = delete;

        void drawFrame() const;

      private:
        float aspectRatio = 0.0F;

        Shader shader;
        model::Model model;

        void onWindowResize(int width, int height);
    };
} // namespace bloom::openGL
