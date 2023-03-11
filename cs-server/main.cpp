// Standard includes
#include <iostream>

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

// Local includes
#include "views.hpp"

int main(int argc, char** argv)
{
    httplib::Server server;
    // httplib::SSLServer server("./cert.pem", "./key.pem");

    server.Get("/", cs_server::views::Root);
    server.Get("/styles/global.css",
               cs_server::views::GlobalCSS);

    server.listen("localhost", 8080);

    return 0;
}