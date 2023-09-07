#pragma once

#include "windowSize.hpp"

#include <functional>

namespace bloom::window {
    using OnResizeCallback = std::function<void(int newWidth, int newHeight)>;

    class Window {
      public:
        Window() = default;
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        virtual ~Window() = default;

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        [[nodiscard]] virtual bool isOpen() const = 0;
        virtual void update() = 0;
        [[nodiscard]] virtual WindowSize getSize() const = 0;
        [[nodiscard]] virtual int getWidth() const = 0;
        [[nodiscard]] virtual int getHeight() const = 0;
        virtual std::list<OnResizeCallback>::iterator registerOnResizeCallback(const OnResizeCallback& callback) = 0;
        virtual void removeOnResizeCallback(std::list<OnResizeCallback>::iterator iterator) = 0;
    };
} // namespace bloom::window