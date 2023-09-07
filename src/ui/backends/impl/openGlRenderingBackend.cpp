#include "openGlRenderingBackend.hpp"

#include "imgui_impl_opengl3.h"

namespace bloom::ui::backends {
    void OpenGLRenderingBackend::initialize() {
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void OpenGLRenderingBackend::shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
    }

    void OpenGLRenderingBackend::beginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
    }

    void OpenGLRenderingBackend::drawFrame(ImDrawData* drawData) {
        ImGui_ImplOpenGL3_RenderDrawData(drawData);
    }

} // namespace bloom::ui::backends
