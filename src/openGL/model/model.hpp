#pragma once

#include "mesh.hpp"

#include <vector>

namespace bloom::openGL::model {
    struct Model {
        std::vector<Mesh> meshes;
    };
}