#pragma once

#include <glad/glad.h>

namespace bloom::openGL::material {
    struct UniformInput {
        // The layout location as described in the shader
        GLint layoutLocation;
    };
}