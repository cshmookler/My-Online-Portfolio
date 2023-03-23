#include "routing.hpp"

// Standard includes
#include <chrono>
#include <ctime>
#include <exception>

// Local includes
#include "templates.hpp"
#include "utils.hpp"

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

const std::string PATH_TO_ERROR_PAGE = "./views/error.thtml";

void Logger(const httplib::Request& request, const httplib::Response& response)
{
    time_t timeAtRequest = std::time(nullptr);
    std::string readableTimeAtRequest = std::ctime(&timeAtRequest);
    readableTimeAtRequest.pop_back();

    std::cout << request.remote_addr << " - [" << readableTimeAtRequest << "] "
              << request.method << " / " << request.version << " "
              << request.path << std::endl;
}

void ErrorHandler(const httplib::Request& request, httplib::Response& response)
{
    std::vector<char> error = LoadFile(
        PATH_TO_ERROR_PAGE, [](std::string& value) { return nullptr; });
    response.set_content(error.data(), error.size(), "text/html");
    response.status = 500;
}

void ExceptionHandler(const httplib::Request& request,
                      httplib::Response& response,
                      std::exception_ptr exceptionPointer)
{
    try {
        std::rethrow_exception(exceptionPointer);
    } catch (std::exception& exception) {
        std::cout << "Error 500 - " << exception.what() << std::endl;
    } catch (...) {
        std::cout << "Error 500" << std::endl;
    }

    std::vector<char> error = LoadFile(
        PATH_TO_ERROR_PAGE, [](std::string& value) { return nullptr; });
    response.set_content(error.data(), error.size(), "text/html");
    response.status = 500;
}

httplib::Server::HandlerResponse PreRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response)
{
    return httplib::Server::HandlerResponse::Unhandled;
}

void ServeFile(const httplib::Request& request,
               httplib::Response& response,
               std::string pathToFile,
               std::string contentType)
{
    timer timer;

    std::vector<char> page = LoadFile(pathToFile, [](std::string& value) {
        std::map<std::string, int> valueMatches;
        return std::to_string(valueMatches.at(value));
    });
    response.set_content(page.data(), page.size(), contentType);

    // std::cout << " (Processed in "
    //           << std::chrono::duration_cast<std::chrono::microseconds>(
    //                  timer.Reset())
    //                  .count()
    //           << " μs)" << std::endl;
}

httplib::Server::HandlerResponse PostRoutingHandler(
    const httplib::Request& request,
    httplib::Response& response)
{
    return httplib::Server::HandlerResponse::Unhandled;
}

} // namespace csp
