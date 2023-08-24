#include "texture.h"

#include <stb_image.h>

namespace bloom::openGL {
    Texture::Texture(const std::filesystem::path& imagePath) {
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

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &id);
    }
} // namespace bloom::openGL
