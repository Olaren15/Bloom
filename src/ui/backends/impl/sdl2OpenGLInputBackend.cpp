#include "sdl2OpenGLInputBackend.hpp"

#include "imgui_impl_sdl2.h"
#include "SDL2/SDL.h"

namespace bloom::ui::backends {
    SDL2OpenGLInputBackend::SDL2OpenGLInputBackend(window::SDL2OpenGLWindow* sdl2Window) : sdl2Window(sdl2Window) {}

    void SDL2OpenGLInputBackend::initialize() {
        ImGui_ImplSDL2_InitForOpenGL(sdl2Window->getActualSdlWindow(), sdl2Window->getOpenGLContext());

        onSdlEventCallbackRef = sdl2Window->registerOnSdlEventCallback([](const SDL_Event& sdlEvent) {
            ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        });
    }

    void SDL2OpenGLInputBackend::shutdown() {
        sdl2Window->removeOnSdlEventCallback(onSdlEventCallbackRef);
        ImGui_ImplSDL2_Shutdown();
    }

    void SDL2OpenGLInputBackend::beginFrame() {
        ImGui_ImplSDL2_NewFrame();
    }

} // namespace bloom::ui::backends
