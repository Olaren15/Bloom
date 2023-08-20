#include "bloomApp.h"

#include <array>
#include <cmath>
#include <stdexcept>

namespace Bloom {
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

    static constexpr const char* vertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"

        "out vec3 ourColor;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "    ourColor = aColor;\n"
        "}";

    static constexpr const char* fragmentShaderSource =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"

        "void main()\n"
        "{\n"
        "    FragColor = vec4(ourColor, 1.0);\n"
        "}";

    BloomApp::BloomApp() {
        int error = SDL_Init(SDL_INIT_EVERYTHING);
        if (error) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetSwapInterval(-1);

        window = SDL_CreateWindow(
            "Bloom",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );
        if (!window) {
            throw std::runtime_error(SDL_GetError());
        }

        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            throw std::runtime_error(SDL_GetError());
        }

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

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

        GLuint vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        validateShaderCompilation(vertexShader);

        GLuint fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        validateShaderCompilation(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        validateShaderLinking(shaderProgram);

        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    BloomApp::~BloomApp() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void BloomApp::run() {
        while (!windowShouldClose) {
            processEvents();
            drawFrame();
            SDL_GL_SwapWindow(window);
        }
    }

    void BloomApp::processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                windowShouldClose = true;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                }
            }
        }
    }

    void BloomApp::drawFrame() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void BloomApp::validateShaderCompilation(GLuint shader) {
        GLint compilationSuccess = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationSuccess);
        if (!compilationSuccess) {
            GLint logLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> logMessage(logLength);
            glGetShaderInfoLog(shader, logLength, nullptr, logMessage.data());
            throw std::runtime_error(logMessage.data());
        }
    }

    void BloomApp::validateShaderLinking(GLuint shaderProgram) {
        GLint linkingSuccess = 0;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkingSuccess);
        if (!linkingSuccess) {
            GLint logLength = 0;
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> logMessage(logLength);
            glGetProgramInfoLog(shaderProgram, logLength, nullptr, logMessage.data());
            throw std::runtime_error(logMessage.data());
        }
    }
} // namespace Bloom