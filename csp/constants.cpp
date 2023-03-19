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

const std::string PATH_TO_LOG_FILE = "./log.txt";

// Template engine constants
const std::string TEMPLATE_EXTENSION = ".thtml";
const char TAB = '\t';
const char NEWLINE = '\n';
const std::string FILE_INCLUDE_START = "{{ ";
const std::string FILE_INCLUDE_END = " }}";
const std::string VALUE_INCLUDE_START = "[[ ";
const std::string VALUE_INCLUDE_END = " ]]";
const bool FILE_INCLUDE = false;
const bool VALUE_INCLUDE = true;

// Error messages
const char* ERR_INVALID_RANGE = "ERROR - Invalid Range";

} // namespace csp
