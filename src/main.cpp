// Standard includes
#include <iostream>

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

int main(int argc, char** argv)
{
    httplib::Server server;
    // httplib::SSLServer server("./cert.pem", "./key.pem");

    server.Get("/", [](const httplib::Request&, httplib::Response& response) {
        response.set_content("This is a test.", "text/plain");
    });

    server.listen("0.0.0.0", 8080);

    return 0;
}