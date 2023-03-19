#pragma once

// Standard includes
#include <string>
#include <vector>

namespace csp {

struct file_route
{
    const char* routePattern;
    const char* pathToFile;
    const char* contentType;
};

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

} // csp