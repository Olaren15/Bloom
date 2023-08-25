#pragma once

#include <glad/glad.h>

namespace bloom::openGL::material {

    struct ShaderInputFormat {
        // The number of components (ex: 2 = vec2, 3 = vec3, etc...)
        GLint componentCount;
        // The type of the components (float, uint, etc...)
        GLenum unitType;
    };

}
