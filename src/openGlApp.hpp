#pragma once

#include "openGL/renderer.hpp"
#include "window/impl/openGlWindow.hpp"

namespace bloom {

    class OpenGLApp {
      public:
        OpenGLApp();
        void run();

      private:
        window::OpenGlWindow window;
        openGL::Renderer renderer;
    };

} // namespace bloom