#include "bloomApp.h"

namespace Bloom {
    static constexpr int windowWidth = 1920;
    static constexpr int windowHeight = 1080;

    void BloomApp::run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    void BloomApp::initWindow() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(
            "Bloom",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN
        );
    }

    void BloomApp::initVulkan() {}

    void BloomApp::mainLoop() {
        while (!windowShouldClose) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    windowShouldClose = true;
                }
            }
        }
    }

    void BloomApp::cleanup() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
} // namespace Bloom