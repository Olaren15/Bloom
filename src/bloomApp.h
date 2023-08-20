#pragma once

#include "openGL/shader.h"
#include "window/openGlWindow.h"

#include <glad/glad.h>
#include <vector>

namespace bloom {

    class BloomApp {
      public:
        BloomApp();
        ~BloomApp();
        void run();

      private:
        window::OpenGlWindow window;
        GLuint vao = 0;
        openGl::Shader shader;

        void drawFrame();
    };

} // namespace bloom