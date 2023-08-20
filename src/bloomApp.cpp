#include "bloomApp.h"

#include <array>

namespace bloom {
    static constexpr int windowWidth = 1920;
    static constexpr int windowHeight = 1080;

    // clang-format off
    static constexpr std::array<GLfloat, 18> vertices{
        // positions         // colors
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // top
    };

    static constexpr std::array<GLuint, 6> indices{
        0, 1, 2,
    };

    // clang-format on

    BloomApp::BloomApp() :
        window(windowWidth, windowHeight),
        shader("data/shaders/openGL/shader.vert", "data/shaders/openGl/shader.frag") {
        window.addOnResizeCallback([](int width, int height) { glViewport(0, 0, width, height); });

        glViewport(0, 0, windowWidth, windowHeight);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    BloomApp::~BloomApp() = default;

    void BloomApp::run() {
        while (window.isOpen()) {
            window.update();
            drawFrame();
        }
    }

    void BloomApp::drawFrame() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
} // namespace bloom