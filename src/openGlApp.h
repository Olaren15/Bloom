#pragma once

#include "openGL/renderer.h"
#include "window/openGlWindow.h"

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