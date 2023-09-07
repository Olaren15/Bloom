#pragma once

#include "../window/window.hpp"
#include "backends/inputBackend.hpp"
#include "backends/renderingBackend.hpp"

#include <memory>

namespace bloom::ui {
    class UiRenderer {
      public:
        UiRenderer() = delete;
        UiRenderer(
            std::unique_ptr<backends::InputBackend>&& inputBackend,
            std::unique_ptr<backends::RenderingBackend>&& renderingBackend
        );
        UiRenderer(const UiRenderer&) = delete;
        UiRenderer(UiRenderer&&) = delete;
        ~UiRenderer();

        UiRenderer& operator=(const UiRenderer&) = delete;
        UiRenderer& operator=(UiRenderer&&) = delete;

        void drawFrame();

      private:
        std::unique_ptr<backends::InputBackend> inputBackend;
        std::unique_ptr<backends::RenderingBackend> renderingBackend;
    };
} // namespace bloom::ui