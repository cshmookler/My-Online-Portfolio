#pragma once

// Standard includes
#include <functional>
#include <string>
#include <vector>

namespace csp {

extern const std::string TEMPLATE_EXTENSION;
extern const std::string FILE_INCLUDE_START;
extern const std::string FILE_INCLUDE_END;
extern const std::string VALUE_INCLUDE_START;
extern const std::string VALUE_INCLUDE_END;
extern const bool FILE_INCLUDE;
extern const bool VALUE_INCLUDE;

extern std::string ERR_INVALID_PATH;
extern std::string ERR_INVALID_RANGE;

struct template_include
{
    bool type;
    std::string payload;
    size_t identifierStart;
    size_t identifierEnd;
};

struct template_file
{
    std::string pathToFile;
    size_t identifierStart;
    size_t identifierEnd;
    std::vector<template_include> includes;
};

using MatchIncludeValueToVariable = std::function<std::string(std::string&)>;

std::vector<char> LoadTemplate(const std::string& pathToFile,
                               MatchIncludeValueToVariable matchFunction);

void OverwriteAndInsert(std::vector<char>& first,
                        size_t firstBegin,
                        size_t firstEnd,
                        std::vector<char>& second,
                        size_t secondBegin,
                        size_t secondEnd);

void OverwriteAndInsertFile(std::vector<char>& first,
                            size_t firstBegin,
                            size_t firstOverwriteSize,
                            const std::string& pathToFile,
                            size_t charsToRead);

} // namespace csp