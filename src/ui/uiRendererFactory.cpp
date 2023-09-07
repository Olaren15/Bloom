#include "uiRendererFactory.hpp"

#include "../window/impl/sdl2OpenGLWindow.hpp"
#include "backends/impl/openGlRenderingBackend.hpp"
#include "backends/impl/sdl2OpenGLInputBackend.hpp"
#include "backends/inputBackend.hpp"
#include "backends/renderingBackend.hpp"

#include <stdexcept>

namespace bloom::ui {

    UiRenderer createUiRenderer(
        window::Window* window, window::Backends windowBackendType, rendering::Backends renderingBackendType
    ) {
        std::unique_ptr<backends::InputBackend> inputBackend;
        if (windowBackendType == window::Backends::SDL2 && renderingBackendType == rendering::Backends::OpenGL) {
            inputBackend =
                std::make_unique<backends::SDL2OpenGLInputBackend>(dynamic_cast<window::SDL2OpenGLWindow*>(window));
        } else {
            throw std::runtime_error("Unable to find suitable input backend for UiRenderer");
        }

        std::unique_ptr<backends::RenderingBackend> renderingBackend;
        if (renderingBackendType == rendering::Backends::OpenGL) {
            renderingBackend = std::make_unique<backends::OpenGLRenderingBackend>();
        } else {
            throw std::runtime_error("Unable to find suitable rendering backend for UiRenderer");
        }

        return UiRenderer{std::move(inputBackend), std::move(renderingBackend)};
    }

} // namespace bloom::ui
