#pragma once

#include <SDL2/SDL.h>

namespace Bloom {

    class BloomApp {
      public:
        void run();

      private:
        SDL_Window* window = nullptr;
        bool windowShouldClose = false;

        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
    };

} // namespace Bloom