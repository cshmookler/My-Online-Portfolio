#pragma once

// Standard includes
#include <array>
#include <string>

// Local includes
#include "types.hpp"

namespace csp {

extern const std::array<file_route, 9> ROUTES;

extern const std::string PATH_TO_LOG_FILE;

// Template engine constants
extern const std::string TEMPLATE_EXTENSION;
extern const char TAB;
extern const char NEWLINE;
extern const std::string FILE_INCLUDE_START;
extern const std::string FILE_INCLUDE_END;
extern const std::string VALUE_INCLUDE_START;
extern const std::string VALUE_INCLUDE_END;
extern const bool FILE_INCLUDE;
extern const bool VALUE_INCLUDE;

// Error messages
extern const char* ERR_INVALID_RANGE;

} // namespace csp
