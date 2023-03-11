#pragma once

// Standard includes
#include <string>
#include <vector>

namespace cs_server {

namespace utils {

std::vector<char> LoadFile(std::string pathToFile);

} // namespace utils

} // namespace cs_server