#include "bloomApp.h"

#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    bloom::BloomApp bloomApp{};

    try {
        bloomApp.run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}