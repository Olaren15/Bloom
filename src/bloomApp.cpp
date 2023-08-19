#include "bloomApp.h"

#include "validationHelper.h"

#include <SDL2/SDL_vulkan.h>
#include <stdexcept>
#include <vector>

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
        int error = SDL_Init(SDL_INIT_VIDEO);
        if (error) {
            throw std::runtime_error(SDL_GetError());
        }

        window = SDL_CreateWindow(
            "Bloom",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN
        );
        if (!window) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    void BloomApp::initVulkan() {
        validateVkResult(volkInitialize());
        createInstance();
    }

    void BloomApp::createInstance() {
        VkApplicationInfo applicationInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Bloom",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "Bloom",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0,
        };

        unsigned int count = 0;
        SDL_bool success = SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr);
        if (!success) {
            throw std::runtime_error(SDL_GetError());
        }
        std::vector<char const*> extensions{count};
        success = SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data());
        if (!success) {
            throw std::runtime_error(SDL_GetError());
        }

        VkInstanceCreateInfo instanceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &applicationInfo,
            .enabledExtensionCount = count,
            .ppEnabledExtensionNames = extensions.data(),
        };

        validateVkResult(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
        volkLoadInstance(instance);
    }

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
        vkDestroyInstance(instance, nullptr);

        SDL_DestroyWindow(window);
        SDL_Quit();
    }
} // namespace Bloom