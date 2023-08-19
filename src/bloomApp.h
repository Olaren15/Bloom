#pragma once

#include <SDL2/SDL.h>
#include <volk.h>
#include <vector>

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
        std::vector<char const*> getRequiredExtensions();
        static bool areValidationLayersPresent();
        void mainLoop();
        void cleanup();
    };

} // namespace Bloom