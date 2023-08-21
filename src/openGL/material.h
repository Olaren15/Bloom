#pragma once

#include <glad/glad.h>

namespace bloom::openGL {

    struct Material {
        GLuint vertexPositionLayoutLocation;
        GLint vertexPositionComponentsCount;
        GLuint vertexColorLayoutLocation;
        GLint vertexColorComponentsCount;
    };

    static const Material defaultMaterial{0, 3, 1, 3};

} // namespace bloom::openGL
