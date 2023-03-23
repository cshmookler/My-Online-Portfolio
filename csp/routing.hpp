#pragma once

// Standard includes
#include <string>

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

namespace csp {

struct file_route
{
    const char* routePattern;
    const char* pathToFile;
    const char* contentType;
};

extern const std::array<file_route, 9> ROUTES;

extern const std::string PATH_TO_ERROR_PAGE;

void Logger(const httplib::Request& request, const httplib::Response& response);

void ErrorHandler(const httplib::Request& request, httplib::Response& response);

void ExceptionHandler(const httplib::Request& request,
                      httplib::Response& response,
                      std::exception_ptr exceptionPointer);

httplib::Server::HandlerResponse PreRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response);

void ServeFile(const httplib::Request& request,
               httplib::Response& response,
               std::string pathToFile,
               std::string contentType);

httplib::Server::HandlerResponse PostRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response);

} // namespace csp
