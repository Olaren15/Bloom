#pragma once

#include "model.hpp"
#include <filesystem>

namespace bloom::openGL::model {
    Model importModelFromFile(const std::filesystem::path& path);
}