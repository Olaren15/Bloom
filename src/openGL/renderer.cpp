#include "renderer.h"

#include "model/cube.h"
#include "model/vertex.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ranges>
#include <SDL_timer.h>

namespace bloom::openGL {
    Renderer::Renderer(window::OpenGlWindow* window) :
        shader{"data/shaders/openGL/default.vert.glsl", "data/shaders/openGL/default.frag.glsl"},
        rem{"data/images/rem.jpg"},
        tramway{"data/images/tramway.jpg"},
        defaultMaterial{
            &shader,
            {{{"position"}, {0, {3, GL_FLOAT}}}, {"uv", {1, {2, GL_FLOAT}}}},
            {{"rem", {2, 0, &rem}}, {"tramway", {3, 1, &tramway}}},
            {{"model", {0}}, {"projection", {1}}}} {
        window->addOnResizeCallback([this](const int width, const int height) { onWindowResize(width, height); });

        const auto [width, height] = window->getSize();
        onWindowResize(width, height);

        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(Cube.vertices.size() * sizeof(model::Vertex)),
            Cube.vertices.data(),
            GL_STATIC_DRAW
        );

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(Cube.indices.size() * sizeof(model::Index)),
            Cube.indices.data(),
            GL_STATIC_DRAW
        );

        const auto& positionInput = defaultMaterial.bufferInputs.at("position");
        glVertexAttribPointer(
            positionInput.layoutLocation,
            positionInput.format.componentCount,
            positionInput.format.unitType,
            GL_FALSE,
            sizeof(model::Vertex),
            reinterpret_cast<GLvoid*>(offsetof(model::Vertex, position)) // NOLINT(performance-no-int-to-ptr)
        );
        glEnableVertexAttribArray(positionInput.layoutLocation);

        const auto& uvInput = defaultMaterial.bufferInputs.at("uv");
        glVertexAttribPointer(
            uvInput.layoutLocation,
            uvInput.format.componentCount,
            uvInput.format.unitType,
            GL_FALSE,
            sizeof(model::Vertex),
            reinterpret_cast<GLvoid*>(offsetof(model::Vertex, uv)) // NOLINT(performance-no-int-to-ptr)
        );
        glEnableVertexAttribArray(uvInput.layoutLocation);
        glBindVertexArray(0);

        glUseProgram(*defaultMaterial.shader);
        for (const auto& [layoutLocation, textureUnit, texture] : std::views::values(defaultMaterial.textureInputs)) {
            glUniform1i(layoutLocation, textureUnit);
        }
    }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void Renderer::drawFrame() const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(*defaultMaterial.shader);

        for (const auto& [layoutLocation, textureUnit, texture] : std::views::values(defaultMaterial.textureInputs)) {
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            glBindTexture(GL_TEXTURE_2D, *texture);
        }

        auto model = rotate(
            glm::identity<glm::mat4>(),
            static_cast<float>(SDL_GetTicks64()) / 1000.0f * glm::radians(-50.0f),
            glm::vec3{0.0f, 1.0f, 0.0f}
        );
        const auto view =
            lookAt(glm::vec3{-1.0f, 1.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
        projection = projection * view;

        glUniformMatrix4fv(defaultMaterial.uniformInputs.at("model").layoutLocation, 1, GL_FALSE, value_ptr(model));
        glUniformMatrix4fv(
            defaultMaterial.uniformInputs.at("projection").layoutLocation, 1, GL_FALSE, value_ptr(projection)
        );

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Cube.indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void Renderer::onWindowResize(const int width, const int height) {
        glViewport(0, 0, width, height);
        aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }
} // namespace bloom::openGL