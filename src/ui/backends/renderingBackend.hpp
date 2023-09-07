#pragma once

#include "imgui.h"
#include "platformBackend.hpp"

namespace bloom::ui::backends {

    class RenderingBackend : public PlatformBackend {
      public:
        RenderingBackend() = default;
        RenderingBackend(const RenderingBackend&) = default;
        RenderingBackend(RenderingBackend&&) = default;
        ~RenderingBackend() override = default;

        RenderingBackend& operator=(const RenderingBackend&) = default;
        RenderingBackend& operator=(RenderingBackend&&) = default;

        virtual void drawFrame(ImDrawData* drawData) = 0;
    };

} // namespace bloom::ui::backends
