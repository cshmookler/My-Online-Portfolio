#pragma once

// Standard includes
#include <chrono>
#include <string>

// Local includes
#include "types.hpp"

namespace csp {

void OverwriteAndInsert(char_buffer& first,
                        size_t firstBegin,
                        size_t firstEnd,
                        char_buffer& second,
                        size_t secondBegin,
                        size_t secondEnd);

char_buffer LoadFile(std::string& pathToFile);

char_buffer LoadTemplate(std::string& pathToFile);

class timer
{
    std::chrono::system_clock::time_point timeAtLastReset_;

  public:
    timer();
    std::chrono::system_clock::duration Reset();
};

} // namespace csp
