// Standard includes
#include <iostream>

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

// Local includes
#include "routing.hpp"
#include "templates.hpp"
#include "utils.hpp"

int main(int argc, char** argv)
{
    httplib::Server server;
    // httplib::SSLServer server("ssl/cert.pem", "ssl/key.pem");

    server.set_logger(csp::Logger);
    server.set_error_handler(csp::ErrorHandler);
    server.set_exception_handler(csp::ExceptionHandler);
    server.set_pre_routing_handler(csp::PreRoutingHandler);
    server.set_post_routing_handler(csp::PostRoutingHandler);

    for (const auto& route : csp::ROUTES) {
        server.Get(route.routePattern,
                   [&route](const httplib::Request& request,
                            httplib::Response& response) -> void {
                       csp::ServeFile(request,
                                      response,
                                      route.pathToFile,
                                      route.contentType);
                   });
    }

    server.listen("0.0.0.0", 8080);

    return 0;
}