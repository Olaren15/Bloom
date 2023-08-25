#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL::material {

    struct Shader {
        Shader() = delete;
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        Shader(const Shader&) = delete;
        Shader(const Shader&&) = delete;
        ~Shader();

        Shader& operator=(const Shader&) = delete;
        Shader& operator=(const Shader&&) = delete;
        operator GLuint() const;

        GLuint id;

      private:
        static void validateShaderCompilation(GLuint shader);
        static void validateShaderLinking(GLuint shaderProgram);
    };

} // namespace bloom::openGL::material
