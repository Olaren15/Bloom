#include "openGlApp.hpp"

#include "rendering/backends.hpp"
#include "ui/uiRendererFactory.hpp"
#include "window/backends.hpp"

namespace bloom {
    static constexpr int WindowWidth = 1920;
    static constexpr int WindowHeight = 1080;

    static constexpr rendering::Backends renderingBackend = rendering::Backends::OpenGL;
    static constexpr window::Backends windowBackend = window::Backends::SDL2;

    OpenGLApp::OpenGLApp() :
      window(WindowWidth, WindowHeight),
      graphicsRenderer(&window),
      uiRenderer(ui::createUiRenderer(&window, windowBackend, renderingBackend)) {}

    void OpenGLApp::run() {
        while (window.isOpen()) {
            window.update();
            graphicsRenderer.drawFrame();
            uiRenderer.drawFrame();
        }
    }
} // namespace bloom