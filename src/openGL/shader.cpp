#include "shader.h"

#include "../filesystem/fileReader.h"

#include <vector>

namespace bloom::openGl {
    Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath) {
        std::string vertexCode = filesystem::readFileToString(vertexPath);
        std::string fragmentCode = filesystem::readFileToString(fragmentPath);

        const char* pVertexCode = vertexCode.c_str();
        const char* pFragmentCode = fragmentCode.c_str();

        GLuint vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &pVertexCode, nullptr);
        glCompileShader(vertexShader);
        validateShaderCompilation(vertexShader);

        GLuint fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &pFragmentCode, nullptr);
        glCompileShader(fragmentShader);
        validateShaderCompilation(fragmentShader);

        programId = glCreateProgram();
        glAttachShader(programId, vertexShader);
        glAttachShader(programId, fragmentShader);
        glLinkProgram(programId);
        validateShaderLinking(programId);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::use() const {
        glUseProgram(programId);
    }

    GLuint Shader::getId() const {
        return programId;
    }

    void Shader::validateShaderCompilation(GLuint shader) {
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

    void Shader::validateShaderLinking(GLuint shaderProgram) {
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

    Shader::~Shader() {
        glDeleteProgram(programId);
    }

} // namespace bloom::openGl