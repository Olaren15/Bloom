#pragma once

#include "../../../window/impl/sdl2OpenGLWindow.hpp"
#include "../inputBackend.hpp"

namespace bloom::ui::backends {

    class SDL2OpenGLInputBackend final : public InputBackend {
      public:
        SDL2OpenGLInputBackend() = delete;
        SDL2OpenGLInputBackend(window::SDL2OpenGLWindow* sdl2Window); // NOLINT(*-explicit-constructor)
        SDL2OpenGLInputBackend(const SDL2OpenGLInputBackend&) = default;
        SDL2OpenGLInputBackend(SDL2OpenGLInputBackend&&) = default;
        ~SDL2OpenGLInputBackend() final = default;

        SDL2OpenGLInputBackend& operator=(const SDL2OpenGLInputBackend&) = default;
        SDL2OpenGLInputBackend& operator=(SDL2OpenGLInputBackend&&) = default;

        void beginFrame() override;
        void initialize() override;
        void shutdown() override;

      private:
        window::SDL2OpenGLWindow* sdl2Window;
        std::list<window::OnSdlEventCallback>::iterator onSdlEventCallbackRef;
    };

} // namespace bloom::ui::imgui::backends
