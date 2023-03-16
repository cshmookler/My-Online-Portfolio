#pragma once

// Standard includes
#include <vector>

namespace csp {

struct file_route
{
    const char* routePattern;
    const char* pathToFile;
    const char* contentType;
};

using char_buffer = std::vector<char>;

} // csp