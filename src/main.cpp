#include "openGlApp.hpp"

#include <exception>
#include <iostream>
#include <SDL2/SDL_main.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    bloom::OpenGLApp bloomApp{};

    try {
        bloomApp.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}