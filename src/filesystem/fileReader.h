#pragma once

#include <filesystem>
#include <string>

namespace bloom::filesystem {

    std::string readFileToString(const std::filesystem::path& path);

}
