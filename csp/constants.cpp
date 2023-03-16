#include "constants.hpp"

namespace csp {

const std::array<file_route, 9> ROUTES = {
    { { "/", "./views/index.thtml", "text/html" },
      { "/about-me", "./views/about-me.thtml", "text/html" },
      { "/resume", "./views/resume.thtml", "text/html" },
      { "/independant-projects",
        "./views/independant-projects.thtml",
        "text/html" },
      { "/club-u", "./views/club-u.thtml", "text/html" },
      { "/styles/global.css", "./styles/global.css", "text/css" },
      { "/images/touring.jpg", "./images/touring.jpg", "image/jpeg" },
      { "/images/self-portrait.jpg",
        "./images/self-portrait.jpg",
        "image/jpeg" },
      { "/images/camping.jpg", "./images/camping.jpg", "image/jpeg" } }
};

const std::string TEMPLATE_EXTENSION = ".thtml";

// Template engine constants
const char TAB = '\t';
const char NEWLINE = '\n';
const std::string TEMPLATE_REF_START = "{{ ";
const std::string TEMPLATE_REF_END = " }}";
const std::string TEMPLATE_VALUE_START = "[[ ";
const std::string TEMPLATE_VALUE_END = " ]]";

// Error messages
const char* ERR_INVALID_RANGE = "ERROR - Invalid Range";

} // namespace csp
