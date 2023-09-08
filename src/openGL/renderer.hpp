#pragma once

#include "../window/impl/sdl2OpenGLWindow.hpp"
#include "../window/window.hpp"
#include "model/model.hpp"
#include "shader.hpp"

namespace bloom::openGL {

    class Renderer {
      public:
        Renderer() = delete;
        explicit Renderer(window::SDL2OpenGLWindow* window);
        void updateMatrices() const;
        Renderer(const Renderer&) = delete;
        Renderer(const Renderer&&) = delete;
        ~Renderer();

        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(const Renderer&&) = delete;

        void setModel(const std::filesystem::path& modelPath);
        void drawFrame() const;

      private:
        float aspectRatio = 0.0F;

        Shader shader;
        std::unique_ptr<model::Model> model = nullptr;
        window::SDL2OpenGLWindow* window;
        std::list<window::OnResizeCallback>::iterator onResizeCallbackRef;

        void onWindowResize(int width, int height);
    };
} // namespace bloom::openGL
