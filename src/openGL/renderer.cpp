#include "renderer.hpp"

#include "model/modelImporter.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <SDL_timer.h>

constexpr float MillisecondsPerSeconds = 1000.0F;
constexpr float RotationDegreesPerSecond = 50.0F;
constexpr float FieldOfView = 90.0F;
constexpr float NearPlane = 0.1F;
constexpr float FarPlane = 100.0F;

namespace bloom::openGL {
    Renderer::Renderer(window::OpenGlWindow* window) :
      shader{"data/shaders/openGL/default.vert.glsl", "data/shaders/openGL/default.frag.glsl"},
      model{model::importModelFromFile("D:/Downloads/silent_ash/scene.gltf")} {
        window->addOnResizeCallback([this](const int width, const int height) { onWindowResize(width, height); });

        const auto [width, height] = window->getSize();
        onWindowResize(width, height);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(
            []([[maybe_unused]] GLenum source, // NOLINT(*-easily-swappable-parameters)
               [[maybe_unused]] GLenum type,
               [[maybe_unused]] GLuint id, // NOLINT(*-identifier-length)
               [[maybe_unused]] GLenum severity,
               [[maybe_unused]] GLsizei length,
               const GLchar* message,
               [[maybe_unused]] const void* userParam) { std::cout << message << "\n"; },
            nullptr
        );
    }

    void Renderer::drawFrame() const {
        glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        updateMatrices();

        for (const model::Mesh& mesh : model.meshes) {
            glUniform1i(4, 0); // Use texture 0 for our baseColor sampler
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh.texture);

            glBindVertexArray(mesh.vertexArray);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.indices.size()), GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::updateMatrices() const {
        auto modelMat = rotate(
            glm::identity<glm::mat4>(),
            static_cast<float>(SDL_GetTicks64()) / MillisecondsPerSeconds * glm::radians(RotationDegreesPerSecond),
            glm::vec3{0.0F, 1.0F, 0.0F}
        );
        const auto viewMat =
            lookAt(glm::vec3{0.0F, 1.0F, 4.0F}, glm::vec3{0.0F, 0.0F, 0.0F}, glm::vec3{0.0F, 1.0F, 0.0F});
        glm::mat4 projectionMat = glm::perspective(glm::radians(FieldOfView), aspectRatio, NearPlane, FarPlane);
        const auto combinedProjectionViewMat = projectionMat * viewMat;

        glUniformMatrix4fv(0, 1, GL_FALSE, value_ptr(modelMat));
        glUniformMatrix4fv(1, 1, GL_FALSE, value_ptr(viewMat));
        glUniformMatrix4fv(2, 1, GL_FALSE, value_ptr(projectionMat));
        glUniformMatrix4fv(3, 1, GL_FALSE, value_ptr(combinedProjectionViewMat));
    }

    void Renderer::onWindowResize(const int width, const int height) {
        glViewport(0, 0, width, height);
        aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }
} // namespace bloom::openGL