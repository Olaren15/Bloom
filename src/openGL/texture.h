#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL {

    struct Texture {
        Texture() = delete;
        explicit Texture(const std::filesystem::path& imagePath);
        Texture(const Texture&) = delete;
        Texture(const Texture&&) = delete;
        ~Texture();

        Texture& operator=(const Texture&) = delete;
        Texture& operator=(const Texture&&) = delete;
        operator GLuint() const;

        GLuint id = 0;
    };

} // namespace bloom::openGL
