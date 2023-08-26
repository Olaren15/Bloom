#include "fileReader.hpp"

#include <fstream>

namespace bloom::filesystem {
    std::string readFileToString(const std::filesystem::path& path) {
        std::ifstream fileStream(path);
        fileStream.exceptions(std::ifstream::failbit | std::ifstream ::badbit);

        std::string content{};
        content.reserve(file_size(path));
        content.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());

        return content;
    }
} // namespace bloom::filesystem
