#include "openGlApp.h"

namespace bloom {
    static constexpr int windowWidth = 1920;
    static constexpr int windowHeight = 1080;

    OpenGLApp::OpenGLApp() : window(windowWidth, windowHeight), renderer(window) {}

    void OpenGLApp::run() {
        while (window.isOpen()) {
            window.update();
            renderer.drawFrame();
        }
    }
} // namespace bloom