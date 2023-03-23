#include "utils.hpp"

// Standard includes
#include <filesystem>
#include <fstream>

// Local includes
#include "templates.hpp"

namespace csp {

const std::string PATH_TO_LOG_FILE = "./log.txt";

std::vector<char> LoadFile(const std::string& pathToFile,
                           MatchIncludeValueToVariable matchFunction)
{
    std::filesystem::path path(pathToFile);

    if (path.extension() == TEMPLATE_EXTENSION) {
        return LoadTemplate(pathToFile, matchFunction);
    }

    std::vector<char> charBuffer(std::filesystem::file_size(path));

    std::ifstream file(pathToFile);
    if (!file.is_open()) {
        throw std::runtime_error(ERR_INVALID_PATH);
    }

    for (char& character : charBuffer) {
        character = char(file.get());
    }

    file.close();

    return charBuffer;
}

timer::timer()
{
    this->timeAtLastReset_ = std::chrono::system_clock::now();
}

std::chrono::system_clock::duration timer::Reset()
{
    std::chrono::system_clock::time_point previousTimeAtLastReset =
        this->timeAtLastReset_;
    this->timeAtLastReset_ = std::chrono::system_clock::now();
    return (this->timeAtLastReset_ - previousTimeAtLastReset);
}

void Log(const char* chars, size_t size)
{
    std::ofstream logFile(PATH_TO_LOG_FILE,
                          std::ios_base::out | std::ios_base::app);
    if (!logFile.is_open()) {
        throw std::runtime_error(ERR_INVALID_RANGE);
    }

    logFile << "\n--BEGIN--\n";
    logFile.write(chars, size);
    logFile << "\n--END--\n";

    logFile.close();
}

} // namespace csp
