#pragma once

// External includes
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../external/cpp-httplib-0.12.1/httplib.h"

namespace cs_server {

namespace views {

void GlobalCSS(const httplib::Request& request,
               httplib::Response& response);

void Root(const httplib::Request& request,
          httplib::Response& response);

} // namespace views

} // namespace cs_server
