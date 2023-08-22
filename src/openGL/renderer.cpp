#include "renderer.h"

#include <array>

namespace bloom::openGL {
    // clang-format off
    static constexpr std::array<GLfloat, 20> vertices{
        // positions            // texture uv
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,   // top left
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f,   // top right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
    };

    static constexpr std::array<GLuint, 6> indices{
        0, 1, 3,
        0, 3, 2
    };

    // clang-format on

    Renderer::Renderer(window::OpenGlWindow& window) :
        window(window),
        shader("data/shaders/openGL/default.vert.glsl", "data/shaders/openGL/default.frag.glsl"),
        rem("data/images/rem.jpg"),
        tramway("data/images/tramway.jpg"),
        defaultMaterial(
            shader,
            {{{"position"}, {0, {3, GL_FLOAT}}}, {"uv", {1, {2, GL_FLOAT}}}},
            {{"rem", {0, 0, rem}}, {"tramway", {1, 1, tramway}}}
        ) {
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

        auto positionInput = defaultMaterial.bufferInputs.at("position");
        glVertexAttribPointer(
            positionInput.layoutLocation,
            positionInput.format.componentCount,
            positionInput.format.unitType,
            GL_FALSE,
            5 * sizeof(GLfloat),
            reinterpret_cast<GLvoid*>(0)
        );
        glEnableVertexAttribArray(positionInput.layoutLocation);

        auto uvInput = defaultMaterial.bufferInputs.at("uv");
        glVertexAttribPointer(
            uvInput.layoutLocation,
            uvInput.format.componentCount,
            uvInput.format.unitType,
            GL_FALSE,
            5 * sizeof(GLfloat),
            reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(uvInput.layoutLocation);

        glBindVertexArray(0);

        glUseProgram(defaultMaterial.shader.id);

        auto reemTextureInput = defaultMaterial.textureInputs.at("rem");
        glUniform1i(reemTextureInput.layoutLocation, reemTextureInput.textureUnit);

        auto tramwayTextureInput = defaultMaterial.textureInputs.at("tramway");
        glUniform1i(tramwayTextureInput.layoutLocation, tramwayTextureInput.textureUnit);
    }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void Renderer::drawFrame() const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(defaultMaterial.shader.id);

        for (auto [texName, texInput] : defaultMaterial.textureInputs) {
            glActiveTexture(GL_TEXTURE0 + texInput.textureUnit);
            glBindTexture(GL_TEXTURE_2D, texInput.texture.id);
        }
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
} // namespace bloom::openGL
