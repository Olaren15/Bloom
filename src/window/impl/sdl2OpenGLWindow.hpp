#pragma once

#include "../window.hpp"

#include <iterator>
#include <SDL2/SDL.h>

namespace bloom::window {
    using OnSdlEventCallback = std::function<void(const SDL_Event& event)>;

    class SDL2OpenGLWindow final : public Window {
      public:
        SDL2OpenGLWindow(int width, int height);
        SDL2OpenGLWindow(const SDL2OpenGLWindow&) = delete;
        SDL2OpenGLWindow(const SDL2OpenGLWindow&&) = delete;
        ~SDL2OpenGLWindow() override;

        SDL2OpenGLWindow& operator=(const SDL2OpenGLWindow&) = delete;
        SDL2OpenGLWindow& operator=(const SDL2OpenGLWindow&&) = delete;

        [[nodiscard]] bool isOpen() const override;
        void update() override;
        [[nodiscard]] WindowSize getSize() const override;
        [[nodiscard]] int getWidth() const override;
        [[nodiscard]] int getHeight() const override;
        std::list<OnResizeCallback>::iterator registerOnResizeCallback(const OnResizeCallback& callback) override;
        void removeOnResizeCallback(std::list<OnResizeCallback>::iterator iterator) override;

        [[nodiscard]] SDL_Window* getActualSdlWindow();
        [[nodiscard]] SDL_GLContext getOpenGLContext();
        std::list<OnSdlEventCallback>::iterator registerOnSdlEventCallback(const OnSdlEventCallback& callback);
        void removeOnSdlEventCallback(std::list<OnSdlEventCallback>::iterator iterator);

      private:
        SDL_Window* window = nullptr;
        SDL_GLContext glContext = nullptr;
        bool shouldWindowClose = false;
        std::list<OnResizeCallback> onResizeCallbacks{};
        std::list<OnSdlEventCallback> onSdlEventCallbacks{};
    };

} // namespace bloom::window
