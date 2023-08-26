#include "openGlApp.hpp"

namespace bloom {
    static constexpr int WindowWidth = 1920;
    static constexpr int WindowHeight = 1080;

    OpenGLApp::OpenGLApp() : window(WindowWidth, WindowHeight), renderer(&window) {}

    void OpenGLApp::run() {
        while (window.isOpen()) {
            window.update();
            renderer.drawFrame();
        }
    }
}