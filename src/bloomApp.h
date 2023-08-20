#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>

namespace Bloom {

    class BloomApp {
      public:
        BloomApp();
        ~BloomApp();
        void run();

      private:
        SDL_Window* window = nullptr;
        SDL_GLContext glContext = nullptr;
        bool windowShouldClose = false;
        GLuint vao = 0;
        GLuint shaderProgram = 0;

        void processEvents();
        void drawFrame();

        static void validateShaderCompilation(GLuint shader);
        static void validateShaderLinking(GLuint shaderProgram);
    };

} // namespace Bloom