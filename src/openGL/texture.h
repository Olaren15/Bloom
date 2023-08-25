#pragma once

#include <filesystem>
#include <glad/glad.h>

namespace bloom::openGL {

    struct Texture {
        explicit Texture(const std::filesystem::path& imagePath);
        ~Texture();
        GLuint id = 0;
    };

} // namespace bloom::openGL
