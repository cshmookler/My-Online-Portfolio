#include "views.hpp"

// Standard includes
#include <fstream>
#include <streambuf>

// Local includes
#include "utils.hpp"

namespace cs_server {

void views::GlobalCSS(const httplib::Request& request,
                      httplib::Response& response)
{
    std::vector<char> css =
        utils::LoadFile("styles/global.css");
    response.set_content(
        css.data(), css.size(), "text/css");
}

void views::Root(const httplib::Request& request,
                 httplib::Response& response)
{
    std::vector<char> pageContent =
        utils::LoadFile("views/index.html");
    response.set_content(pageContent.data(),
                         pageContent.size(),
                         "text/html");
    std::cout << request.remote_addr << ":"
              << request.remote_port << std::endl;
}

} // namespace cs_server