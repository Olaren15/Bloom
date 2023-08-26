#include "openGlWindow.hpp"

#include <algorithm>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdexcept>

namespace bloom::window {

    OpenGlWindow::OpenGlWindow(const int width, const int height) {
        if (SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        if (!SDL_GL_SetSwapInterval(-1)) {
            SDL_GL_SetSwapInterval(1);
        }

        window = SDL_CreateWindow(
            "bloom",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );
        if (!window) {
            throw std::runtime_error(SDL_GetError());
        }

        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            throw std::runtime_error(SDL_GetError());
        }

        // TODO : move the glad loader elsewhere ?? (most likely in the renderer)
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    OpenGlWindow::~OpenGlWindow() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool OpenGlWindow::isOpen() const {
        return !shouldWindowClose;
    }

    void OpenGlWindow::update() {
        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                shouldWindowClose = true;
                break;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    std::ranges::for_each(onResizeCallbacks, [event](const auto& callback) {
                        callback(event.window.data1, event.window.data2);
                    });
                }
            }
        }
    }

    WindowSize OpenGlWindow::getSize() const {
        int width;
        int height;

        SDL_GetWindowSize(window, &width, &height);

        return WindowSize{width, height};
    }

    int OpenGlWindow::getWidth() const {
        return getSize().width;
    }

    int OpenGlWindow::getHeight() const {
        return getSize().height;
    }

    void OpenGlWindow::addOnResizeCallback(const OnResizeCallback& callback) {
        onResizeCallbacks.push_back(callback);
    }

} // namespace bloom::window
