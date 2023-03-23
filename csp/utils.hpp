#pragma once

// Standard includes
#include <chrono>
#include <functional>
#include <string>
#include <vector>

// Local includes
#include "templates.hpp"

namespace csp {

extern const std::string PATH_TO_LOG_FILE;

std::vector<char> LoadFile(const std::string& pathToFile,
                           MatchIncludeValueToVariable matchFunction);

class timer
{
    std::chrono::system_clock::time_point timeAtLastReset_;

  public:
    timer();
    std::chrono::system_clock::duration Reset();
};

void Log(const char* chars, size_t size);

} // namespace csp
