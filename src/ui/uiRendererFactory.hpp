#pragma once

#include "../rendering/backends.hpp"
#include "../window/backends.hpp"
#include "../window/window.hpp"
#include "uiRenderer.hpp"

namespace bloom::ui {

    UiRenderer createUiRenderer(
        window::Window* window, window::Backends windowBackendType, rendering::Backends renderingBackendType
    );

} // namespace bloom::ui
