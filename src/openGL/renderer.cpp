#include "renderer.h"

#include <array>

namespace bloom::openGL {
    // clang-format off
    static constexpr std::array<GLfloat, 24> vertices{
        // positions         // colors
        -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // top left
        0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   // top right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom left
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f    // bottom right
    };

    static constexpr std::array<GLuint, 6> indices{
        0, 1, 3,
        0, 3, 2
    };

    // clang-format on

    Renderer::Renderer(window::OpenGlWindow& window) :
        window(window), shader("data/shaders/openGL/default.vert.glsl", "data/shaders/openGL/default.frag.glsl") {
        window.addOnResizeCallback([](int width, int height) { glViewport(0, 0, width, height); });

        window::WindowSize windowSize = window.getSize();
        glViewport(0, 0, windowSize.width, windowSize.height);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(
            defaultMaterial.vertexPositionLayoutLocation,
            defaultMaterial.vertexPositionComponentsCount,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(GLfloat),
            reinterpret_cast<GLvoid*>(0)
        );
        glEnableVertexAttribArray(defaultMaterial.vertexPositionLayoutLocation);

        glVertexAttribPointer(
            defaultMaterial.vertexColorLayoutLocation,
            defaultMaterial.vertexColorComponentsCount,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(GLfloat),
            reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(defaultMaterial.vertexColorLayoutLocation);

        glBindVertexArray(0);
    }

    void Renderer::drawFrame() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
} // namespace bloom::openGL
