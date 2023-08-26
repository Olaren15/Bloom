#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL {

    struct Texture {
        Texture() = delete;
        explicit Texture(const std::filesystem::path& imagePath);
        Texture(const Texture& other) = delete;
        Texture(Texture&& other) noexcept;
        ~Texture();

        Texture& operator=(const Texture& other) = delete;
        Texture& operator=(Texture&& other) noexcept;
        operator GLuint() const;

        GLuint id = 0;
        std::filesystem::path originalPath;
    };

} // namespace bloom::openGL
