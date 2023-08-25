#pragma once

#include "shaderInputFormat.h"

#include <glad/glad.h>

namespace bloom::openGL::material {

    struct BufferInput {
        // The layout location as described in the fragment shader
        GLuint layoutLocation;
        // The format of this input
        ShaderInputFormat format;
    };

} // namespace bloom::openGL::material
