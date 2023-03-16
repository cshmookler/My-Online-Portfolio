#pragma once

// Standard includes
#include <string>

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

namespace csp {

httplib::Server::HandlerResponse PreRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response);

void ServeFile(const httplib::Request& request,
               httplib::Response& response,
               std::string pathToFile,
               std::string contentType);

} // namespace csp
