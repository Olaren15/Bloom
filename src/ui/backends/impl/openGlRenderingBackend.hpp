#pragma once

#include "../renderingBackend.hpp"

namespace bloom::ui::backends {

    class OpenGLRenderingBackend final : public RenderingBackend {
      public:
        OpenGLRenderingBackend() = default;
        OpenGLRenderingBackend(const OpenGLRenderingBackend&) = default;
        OpenGLRenderingBackend(OpenGLRenderingBackend&&) = default;
        ~OpenGLRenderingBackend() final = default;

        OpenGLRenderingBackend& operator=(const OpenGLRenderingBackend&) = default;
        OpenGLRenderingBackend& operator=(OpenGLRenderingBackend&&) = default;

        void beginFrame() override;
        void drawFrame(ImDrawData* drawData) override;
        void initialize() override;
        void shutdown() override;
    };

} // namespace bloom::ui::imgui::backends
