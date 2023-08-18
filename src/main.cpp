#include <iostream>
#include <SDL2/SDL.h>
#include <volk.h>
#include <glm/glm.hpp>

int main(int argc, char *argv[]) {

    VkResult result = volkInitialize();
    if (result != VK_SUCCESS) {
        std::cout << "Failed to load vulkan" << std::endl;
        return -1;
    }

    uint32_t extensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);

    std::cout << extensionsCount << " extensions supported" << std::endl;

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library" << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Bloom", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);

    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        SDL_Quit();
        return -1;
    }

    bool keepWindowOpen = true;
    while (keepWindowOpen) {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    keepWindowOpen = false;
                    break;
            }
        }
    }

    SDL_Quit();
    return 0;
}
