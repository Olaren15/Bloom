#pragma once

#include "window.hpp"

// ReSharper disable once CppInconsistentNaming
struct SDL_Window;

namespace bloom::window {
    class OpenGlWindow final : public Window {
      public:
        OpenGlWindow(int width, int height);
        OpenGlWindow(const OpenGlWindow&) = delete;
        OpenGlWindow(const OpenGlWindow&&) = delete;
        ~OpenGlWindow() override;

        OpenGlWindow& operator=(const OpenGlWindow&) = delete;
        OpenGlWindow& operator=(const OpenGlWindow&&) = delete;

        [[nodiscard]] bool isOpen() const override;
        void update() override;
        [[nodiscard]] WindowSize getSize() const override;
        [[nodiscard]] int getWidth() const override;
        [[nodiscard]] int getHeight() const override;
        void addOnResizeCallback(const OnResizeCallback& callback) override;

      private:
        SDL_Window* window = nullptr;
        void* glContext = nullptr;
        bool shouldWindowClose = false;
        std::vector<OnResizeCallback> onResizeCallbacks{};
    };

} // namespace bloom::window
