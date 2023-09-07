#pragma once

#include "openGL/renderer.hpp"
#include "window/impl/sdl2OpenGLWindow.hpp"
#include "ui/uiRenderer.hpp"

namespace bloom {

    class OpenGLApp {
      public:
        OpenGLApp();
        void run();

      private:
        window::SDL2OpenGLWindow window;
        openGL::Renderer graphicsRenderer;
        ui::UiRenderer uiRenderer;
    };

} // namespace bloom