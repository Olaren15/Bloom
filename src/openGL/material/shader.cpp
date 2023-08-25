#include "shader.h"

#include "../../filesystem/fileReader.h"

#include <vector>

namespace bloom::openGL::material {
    Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) {
        const std::string vertexCode = filesystem::readFileToString(vertexPath);
        const std::string fragmentCode = filesystem::readFileToString(fragmentPath);

        const char* pVertexCode = vertexCode.c_str();
        const char* pFragmentCode = fragmentCode.c_str();

        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &pVertexCode, nullptr);
        glCompileShader(vertexShader);
        validateShaderCompilation(vertexShader);

        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &pFragmentCode, nullptr);
        glCompileShader(fragmentShader);
        validateShaderCompilation(fragmentShader);

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);
        validateShaderLinking(id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(id);
    }

    Shader::operator GLuint() const {
        return id;
    }

    void Shader::validateShaderCompilation(const GLuint shader) {
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

    void Shader::validateShaderLinking(const GLuint shaderProgram) {
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

}