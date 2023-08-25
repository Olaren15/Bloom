#pragma once

#include "vertex.h"

#include <glad/glad.h>
#include <vector>

namespace bloom::openGL::model {
    using Index = GLuint;

    struct Model {
        std::vector<Vertex> vertices;
        std::vector<Index> indices;
    };
}