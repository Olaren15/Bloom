#include "openGlApp.hpp"

#include "imgui.h"
#include "nfd.h"
#include "rendering/backends.hpp"
#include "ui/uiRendererFactory.hpp"
#include "window/backends.hpp"

#include <iostream>

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
            drawUi();
        }
    }

    void OpenGLApp::drawUi() {
        uiRenderer.startFrame();
        showMenuBar();
        uiRenderer.endFrame();
    }

    void OpenGLApp::showMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open")) {
                    openFile();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void OpenGLApp::openFile() {
        nfdchar_t* chosenFilePath = nullptr;
        nfdresult_t result = NFD_OpenDialog(nullptr, nullptr, &chosenFilePath);

        if (result == NFD_OKAY) {
            graphicsRenderer.setModel(chosenFilePath);
        }
    }
} // namespace bloom