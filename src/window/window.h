#pragma once

#include <functional>
#include <SDL2/SDL.h>

namespace bloom::window {
    class Window {
      public:
        virtual ~Window() = default;

        virtual bool isOpen() = 0;
        virtual void update() = 0;
        virtual void addOnResizeCallback(const std::function<void(int newWidth, int newHeight)>& callback) = 0;
    };
} // namespace bloom::window