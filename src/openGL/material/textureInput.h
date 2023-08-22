#pragma once

#include "../texture.h"

#include <glad/glad.h>

namespace bloom::openGL::material {

    struct TextureInput {
        // The layout location as described in the fragment shader
        GLint layoutLocation;
        // The OpenGL texture unit that should be used for this texture
        GLint textureUnit;
        // A reference to the texture object containing the image data
        const Texture& texture;
    };

} // namespace bloom::openGL::material
