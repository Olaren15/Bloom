#include "sdl2OpenGLWindow.hpp"

#include "glad/glad.h"

#include <algorithm>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <utility>

constexpr int OpenGLVersionMajor = 4;
constexpr int OpenGLVersionMinor = 6;
constexpr int DepthBufferSize = 24;

namespace bloom::window {

    SDL2OpenGLWindow::SDL2OpenGLWindow(const int width, const int height) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OpenGLVersionMajor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OpenGLVersionMinor);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DepthBufferSize);
        if (SDL_GL_SetSwapInterval(-1) == 0) {
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
        if (window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }

        glContext = SDL_GL_CreateContext(window);
        if (glContext == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }

        // TODO : move the glad loader elsewhere ?? (most likely in the renderer)
        if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    SDL2OpenGLWindow::~SDL2OpenGLWindow() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool SDL2OpenGLWindow::isOpen() const {
        return !shouldWindowClose;
    }

    void SDL2OpenGLWindow::update() {
        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                shouldWindowClose = true;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    std::ranges::for_each(onResizeCallbacks, [event](const auto& callback) {
                        callback(event.window.data1, event.window.data2);
                    });
                }
            }

            std::ranges::for_each(onSdlEventCallbacks, [event](const auto& callback) { callback(event); });
        }
    }

    WindowSize SDL2OpenGLWindow::getSize() const {
        int width = 0;
        int height = 0;

        SDL_GetWindowSize(window, &width, &height);

        return WindowSize{width, height};
    }

    int SDL2OpenGLWindow::getWidth() const {
        return getSize().width;
    }

    int SDL2OpenGLWindow::getHeight() const {
        return getSize().height;
    }

    std::list<OnResizeCallback>::iterator SDL2OpenGLWindow::registerOnResizeCallback(const OnResizeCallback& callback) {
        return onResizeCallbacks.insert(onResizeCallbacks.end(), callback);
    }

    void SDL2OpenGLWindow::removeOnResizeCallback(std::list<OnResizeCallback>::iterator iterator) {
        onResizeCallbacks.erase(iterator);
    }

    SDL_Window* SDL2OpenGLWindow::getActualSdlWindow() {
        return window;
    }

    SDL_GLContext SDL2OpenGLWindow::getOpenGLContext() {
        return glContext;
    }

    std::list<OnSdlEventCallback>::iterator
        SDL2OpenGLWindow::registerOnSdlEventCallback(const OnSdlEventCallback& callback) {
        return onSdlEventCallbacks.insert(onSdlEventCallbacks.end(), callback);
    }

    void SDL2OpenGLWindow::removeOnSdlEventCallback(std::list<OnSdlEventCallback>::iterator iterator) {
        onSdlEventCallbacks.erase(std::move(iterator));
    }
} // namespace bloom::window
