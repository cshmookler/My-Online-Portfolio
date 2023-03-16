#pragma once

// Standard includes
#include <array>
#include <string>

// Local includes
#include "types.hpp"

namespace csp {

extern const std::array<file_route, 9> ROUTES;

extern const std::string TEMPLATE_EXTENSION;

// Template engine constants
extern const char TAB;
extern const char NEWLINE;
extern const std::string TEMPLATE_REF_START;
extern const std::string TEMPLATE_REF_END;
extern const std::string TEMPLATE_VALUE_START;
extern const std::string TEMPLATE_VALUE_END;

// Error messages
extern const char* ERR_INVALID_RANGE;

} // namespace csp
