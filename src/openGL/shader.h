#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL {

    class Shader {
      public:
        Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
        ~Shader();
        void use() const;
        [[nodiscard]] GLuint getId() const;

      private:
        GLuint programId;
        static void validateShaderCompilation(GLuint shader);
        static void validateShaderLinking(GLuint shaderProgram);
    };

} // namespace bloom::openGL
