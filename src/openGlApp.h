#pragma once

#include "openGL/renderer.h"
#include "window/openGlWindow.h"

#include <glad/glad.h>
#include <vector>

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