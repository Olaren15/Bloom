#pragma once

#include "bufferInput.h"
#include "textureInput.h"
#include "shader.h"

#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace bloom::openGL::material {

    struct Material {
        // The shader used by the material
        const Shader& shader;
        // Buffer-backed inputs by name
        std::unordered_map<std::string, BufferInput> bufferInputs;
        // Texture inputs by name
        std::unordered_map<std::string, TextureInput> textureInputs;
    };

} // namespace bloom::openGL::material
