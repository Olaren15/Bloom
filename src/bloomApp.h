#pragma once

#include <SDL2/SDL.h>
#include <volk.h>

namespace Bloom {

    class BloomApp {
      public:
        void run();

      private:
        SDL_Window* window = nullptr;
        bool windowShouldClose = false;
        VkInstance instance = nullptr;

        void initWindow();
        void initVulkan();
        void createInstance();
        void mainLoop();
        void cleanup();
    };

} // namespace Bloom