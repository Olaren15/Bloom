#pragma once

#include <glm/glm.hpp>

namespace bloom::openGL::model {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
} // namespace bloom::openGL::model