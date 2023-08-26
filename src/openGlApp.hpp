#pragma once

#include "openGL/renderer.hpp"
#include "window/openGlWindow.hpp"

namespace bloom {

    class OpenGLApp {
      public:
        OpenGLApp();
        void run();

      private:
        window::OpenGlWindow window;
        openGL::Renderer renderer;
    };

}