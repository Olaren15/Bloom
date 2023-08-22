#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL::material {

    struct Shader {
      public:
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        Shader(const Shader& shader) = default;
        ~Shader();

        GLuint id;

      private:
        static void validateShaderCompilation(GLuint shader);
        static void validateShaderLinking(GLuint shaderProgram);
    };

} // namespace bloom::openGL::material
