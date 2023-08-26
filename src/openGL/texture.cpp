#include "texture.hpp"

#include <stb_image.h>

namespace bloom::openGL {
    Texture::Texture(const std::filesystem::path& imagePath) : originalPath(imagePath) {
        int width;
        int height;
        int channels;
        const std::string path = imagePath.string();
        stbi_set_flip_vertically_on_load(true);
        uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 3);

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float maxSupportedAnisotropicFiltering = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxSupportedAnisotropicFiltering);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, maxSupportedAnisotropicFiltering);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    Texture::Texture(Texture&& other) noexcept {
        id = other.id;
        originalPath = other.originalPath;

        other.id = 0;
        other.originalPath = "";
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }

    Texture& Texture::operator=(Texture&& other) noexcept {
        glDeleteTextures(1, &id);

        id = other.id;
        originalPath = other.originalPath;

        other.id = 0;
        other.originalPath = "";

        return *this;
    }

    Texture::operator GLuint() const {
        return id;
    }
} // namespace bloom::openGL
