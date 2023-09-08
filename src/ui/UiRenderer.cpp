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

    void UiRenderer::startFrame() {
        renderingBackend->beginFrame();
        inputBackend->beginFrame();
        ImGui::NewFrame();
    }

    void UiRenderer::endFrame() {
        ImGui::Render();
        renderingBackend->drawFrame(ImGui::GetDrawData());
    }

} // namespace bloom::ui
