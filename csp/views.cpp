#include "views.hpp"

// Standard includes
#include <chrono>
#include <ctime>

// Local includes
#include "constants.hpp"
#include "utils.hpp"

namespace csp {

httplib::Server::HandlerResponse PreRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response)
{
    time_t timeAtRequest = std::time(nullptr);
    std::string readableTimeAtRequest = std::ctime(&timeAtRequest);
    readableTimeAtRequest.pop_back();

    std::cout << request.remote_addr << " - [" << readableTimeAtRequest << "] "
              << request.method << " / " << request.version << " "
              << request.path << std::endl;

    return httplib::Server::HandlerResponse::Unhandled;
}

void ServeFile(const httplib::Request& request,
               httplib::Response& response,
               std::string pathToFile,
               std::string contentType)
{
    // csp::timer timer;
    std::vector<char> page = LoadFile(pathToFile);
    // std::cout << "Time elapsed: "
    //   << std::chrono::duration_cast<std::chrono::milliseconds>(
    //  timer.Reset())
    //  .count()
    //   << timer.Reset().count() << std::endl;
    response.set_content(page.data(), page.size(), contentType);
}

} // namespace csp
