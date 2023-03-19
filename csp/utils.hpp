#pragma once

// Standard includes
#include <chrono>
#include <string>
#include <vector>

namespace csp {

std::vector<char> LoadFile(std::string& pathToFile);

std::vector<char> LoadTemplate(std::string& pathToFile);

void OverwriteAndInsert(std::vector<char>& first,
                        size_t firstBegin,
                        size_t firstEnd,
                        std::vector<char>& second,
                        size_t secondBegin,
                        size_t secondEnd);

void OverwriteAndInsertFile(std::vector<char>& first,
                            size_t firstBegin,
                            size_t firstOverwriteSize,
                            std::string pathToFile,
                            size_t charsToRead);

class timer
{
    std::chrono::system_clock::time_point timeAtLastReset_;

  public:
    timer();
    std::chrono::system_clock::duration Reset();
};

void Log(const char* chars, size_t size);

} // namespace csp
