#pragma once

#include <glad/glad.h>

#include "shaderInputFormat.h"

namespace bloom::openGL::material {

    struct BufferInput {
        // The layout location as described in the fragment shader
        GLuint layoutLocation;
        // The format of this input
        ShaderInputFormat format;
    };

} // namespace bloom::openGL::material
