#pragma once

#include <glm/glm.hpp>

namespace bloom::openGL::model {
    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
    };
}