#include "utils.hpp"

// Standard includes
#include <filesystem>
#include <fstream>

namespace cs_server {

std::vector<char> utils::LoadFile(std::string pathToFile)
{
    std::filesystem::path path(pathToFile);
    size_t fileSize = std::filesystem::file_size(path);
    std::vector<char> fileBuffer(fileSize);

    std::fstream file(pathToFile);
    if (!file.is_open()) {
        return fileBuffer;
    }

    for (size_t i = 0; i < fileSize; i++) {
        fileBuffer.at(i) = char(file.get());
    }

    return fileBuffer;
}

} // namespace cs_server