#include "uiRenderer.hpp"

#include "imgui.h"

namespace bloom::ui {

    UiRenderer::UiRenderer(
        std::unique_ptr<backends::InputBackend>&& inputBackend,
        std::unique_ptr<backends::RenderingBackend>&& renderingBackend
    ) :
      inputBackend(std::move(inputBackend)), renderingBackend(std::move(renderingBackend)) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO imGuiIo = ImGui::GetIO();
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        this->renderingBackend->initialize();
        this->inputBackend->initialize();
    }

    UiRenderer::~UiRenderer() {
        inputBackend->shutdown();
        renderingBackend->shutdown();
        ImGui::DestroyContext();
    }

    void UiRenderer::drawFrame() {
        renderingBackend->beginFrame();
        inputBackend->beginFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        // draw stuff

        ImGui::Render();
        renderingBackend->drawFrame(ImGui::GetDrawData());
    }

} // namespace bloom::ui::imgui
