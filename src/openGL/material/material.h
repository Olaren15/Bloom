#pragma once

#include "bufferInput.h"
#include "shader.h"
#include "textureInput.h"
#include "uniformInput.h"

#include <string>
#include <unordered_map>

namespace bloom::openGL::material {

    struct Material {
        // The shader used by the material
        Shader* shader;
        // Buffer-backed inputs by name
        std::unordered_map<std::string, BufferInput> bufferInputs;
        // Texture inputs by name
        std::unordered_map<std::string, TextureInput> textureInputs;
        // Uniform inputs by name
        std::unordered_map<std::string, UniformInput> uniformInputs;
    };

} // namespace bloom::openGL::material
