#pragma once

#include "windowSize.h"

#include <functional>

namespace bloom::window {
    using OnResizeCallback = std::function<void(int newWidth, int newHeight)>;

    class Window {
      public:
        Window() = default;
        Window(const Window&) = delete;
        Window(const Window&&) = delete;
        virtual ~Window() = default;

        Window& operator=(const Window&) = delete;
        Window& operator=(const Window&&) = delete;

        [[nodiscard]] virtual bool isOpen() const = 0;
        virtual void update() = 0;
        [[nodiscard]] virtual WindowSize getSize() const = 0;
        [[nodiscard]] virtual int getWidth() const = 0;
        [[nodiscard]] virtual int getHeight() const = 0;
        virtual void addOnResizeCallback(const OnResizeCallback& callback) = 0;
    };
}