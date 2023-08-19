#include "bloomApp.h"

#include "validationHelper.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <SDL2/SDL_vulkan.h>
#include <stdexcept>

namespace Bloom {
    static constexpr int windowWidth = 1920;
    static constexpr int windowHeight = 1080;

#ifdef NDEBUG
    static constexpr bool enableValidationLayers = false;
#else
    static constexpr bool enableValidationLayers = true;
#endif

    static constexpr std::array<const char*, 1> validationLayers{"VK_LAYER_KHRONOS_validation"};

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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify" // Do not ask to "simplify" condition based on enableValidationLayer since it
                                          // changes when building in release or debug mode
        if (enableValidationLayers && !areValidationLayersPresent()) {
            throw std::runtime_error("Validation layers requested but not available");
        }

        auto requiredExtension = getRequiredExtensions();

        VkInstanceCreateInfo instanceCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &applicationInfo,
            .enabledLayerCount = enableValidationLayers ? static_cast<uint32_t>(validationLayers.size()) : 0,
            .ppEnabledLayerNames = enableValidationLayers ? validationLayers.data() : nullptr,
            .enabledExtensionCount = static_cast<uint32_t>(requiredExtension.size()),
            .ppEnabledExtensionNames = requiredExtension.data(),
        };
#pragma clang diagnostic pop

        validateVkResult(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));
        volkLoadInstance(instance);
    }

    std::vector<char const*> BloomApp::getRequiredExtensions() {
        unsigned int count = 0;
        SDL_bool success = SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr);
        if (!success) {
            throw std::runtime_error(SDL_GetError());
        }
        std::vector<char const*> requiredExtensions{count};
        success = SDL_Vulkan_GetInstanceExtensions(window, &count, requiredExtensions.data());
        if (!success) {
            throw std::runtime_error(SDL_GetError());
        }

        return requiredExtensions;
    }

    bool BloomApp::areValidationLayersPresent() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        return std::all_of(validationLayers.begin(), validationLayers.end(), [availableLayers](const char* layerName) {
            return std::find_if(
                       availableLayers.begin(),
                       availableLayers.end(),
                       [layerName](const VkLayerProperties& availableLayerProperties) {
                           return strcmp(layerName, availableLayerProperties.layerName) == 0;
                       }
                   )
                   != availableLayers.end();
        });
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