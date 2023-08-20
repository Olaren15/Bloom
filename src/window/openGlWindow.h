#pragma once

#include "window.h"

namespace bloom::window {

    class OpenGlWindow : Window {
      public:
        OpenGlWindow(const int& width, const int& height);
        ~OpenGlWindow() override;

        bool isOpen() override;
        void update() override;
        void addOnResizeCallback(const std::function<void(int, int)>& callback) override;

      private:
        SDL_Window* window = nullptr;
        SDL_GLContext glContext = nullptr;
        bool shouldWindowClose = false;
        std::vector<std::function<void(int, int)>> onResizeCallbacks{};
    };

} // namespace bloom::window
