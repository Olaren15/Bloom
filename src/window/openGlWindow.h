#pragma once

#include "window.h"

namespace bloom::window {

    class OpenGlWindow : Window {
      public:
        OpenGlWindow(int width, int height);
        OpenGlWindow(const OpenGlWindow&) = delete;
        ~OpenGlWindow() override;

        [[nodiscard]] bool isOpen() const override;
        void update() override;
        [[nodiscard]] WindowSize getSize() const override;
        [[nodiscard]] int getWidth() const override;
        [[nodiscard]] int getHeight() const override;
        void addOnResizeCallback(const std::function<void(int, int)>& callback) override;

      private:
        SDL_Window* window = nullptr;
        SDL_GLContext glContext = nullptr;
        bool shouldWindowClose = false;
        std::vector<std::function<void(int, int)>> onResizeCallbacks{};
    };

} // namespace bloom::window