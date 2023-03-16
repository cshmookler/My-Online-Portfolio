#include "utils.hpp"

// Standard includes
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

// Local includes
#include "constants.hpp"

namespace csp {

void OverwriteAndInsert(char_buffer& first,
                        size_t firstBegin,
                        size_t firstEnd,
                        char_buffer& second,
                        size_t secondBegin,
                        size_t secondEnd)
{
    if (firstBegin > firstEnd || secondBegin > secondEnd) {
        // throw ERR_INVALID_RANGE
        return;
    }

    size_t deltaFirst = firstEnd - firstBegin;
    size_t deltaSecond = secondEnd - secondBegin;

    for (size_t index = 0; index < deltaFirst; index++) {
        if (index >= deltaSecond) {
            first.erase(first.begin() + firstBegin + index,
                        first.begin() + firstEnd);
            return;
        }

        first.at(firstBegin + index) = second.at(secondBegin + index);
    }

    first.insert(first.begin() + firstEnd,
                 second.begin() + secondBegin + deltaFirst,
                 second.begin() + secondEnd);
}

csp::char_buffer LoadFile(std::string& pathToFile)
{
    std::filesystem::path path(pathToFile);

    if (path.extension() == TEMPLATE_EXTENSION) {
        std::cout << "loading template" << std::endl;
        return LoadTemplate(pathToFile);
    }

    char_buffer charBuffer(std::filesystem::file_size(path));

    std::fstream file(pathToFile);
    if (!file.is_open()) {
        // throw "Failed to open file"
        return charBuffer;
    }

    for (char& character : charBuffer) {
        character = char(file.get());
    }

    file.close();

    return charBuffer;
}

csp::char_buffer LoadTemplate(std::string& pathToFile)
{
    char_buffer charBuffer(std::filesystem::file_size(pathToFile));

    std::fstream file(pathToFile);
    if (!file.is_open()) {
        return charBuffer;
    }

    int expecting = 0;
    const int WAITING = 0;
    const int REF_START = 1;
    const int REF_END = 2;
    const int VALUE_START = 3;
    const int VALUE_END = 4;

    size_t identifierIndex = 0;
    size_t indexAtPathStart = 0;

    for (size_t charIndex = 0; charIndex < charBuffer.size(); charIndex++) {
        charBuffer.at(charIndex) = char(file.get());
        char& character = charBuffer.at(charIndex);

        switch (expecting) {
            case WAITING:
                if (character == TEMPLATE_REF_START.at(identifierIndex)) {
                    expecting = REF_START;
                    identifierIndex++;
                } else if (character ==
                           TEMPLATE_VALUE_START.at(identifierIndex)) {
                    expecting = VALUE_START;
                    identifierIndex++;
                }
                break;
            case REF_START:
                if (character == TEMPLATE_REF_START.at(identifierIndex)) {
                    identifierIndex++;
                    if (identifierIndex == TEMPLATE_REF_START.size()) {
                        expecting = REF_END;
                        identifierIndex = 0;
                        indexAtPathStart = charIndex + 1;
                    }
                } else {
                    expecting = WAITING;
                    identifierIndex = 0;
                }
                break;
            case REF_END:
                if (character == TEMPLATE_REF_END.at(identifierIndex)) {
                    identifierIndex++;
                    if (identifierIndex == TEMPLATE_REF_END.size()) {
                        std::string pathToRefFile(
                            charBuffer.begin() + indexAtPathStart,
                            charBuffer.begin() + charIndex - identifierIndex +
                                1);
                        std::filesystem::path refPath(pathToRefFile);
                        char_buffer refCharBuffer;
                        if (refPath.extension() == TEMPLATE_EXTENSION) {
                            refCharBuffer = LoadTemplate(pathToRefFile);
                        } else {
                            refCharBuffer = LoadFile(pathToRefFile);
                        }
                        OverwriteAndInsert(charBuffer,
                                           indexAtPathStart -
                                               TEMPLATE_REF_START.size(),
                                           charIndex + 1,
                                           refCharBuffer,
                                           0,
                                           refCharBuffer.size());
                        charIndex += refCharBuffer.size() -
                                     (charIndex - (indexAtPathStart -
                                                   TEMPLATE_REF_START.size()));
                        expecting = WAITING;
                        identifierIndex = 0;
                    }
                }
                break;
            case VALUE_START:
                if (character == TEMPLATE_VALUE_START.at(identifierIndex)) {
                    identifierIndex++;
                    if (identifierIndex == TEMPLATE_VALUE_START.size()) {
                        expecting = VALUE_END;
                        identifierIndex = 0;
                        indexAtPathStart = charIndex + 1;
                    }
                } else {
                    expecting = WAITING;
                    identifierIndex = 0;
                }
                break;
            case VALUE_END:
                if (character == TEMPLATE_VALUE_END.at(identifierIndex)) {
                    identifierIndex++;
                    if (identifierIndex == TEMPLATE_VALUE_END.size()) {
                        char_buffer value(charBuffer.begin() + indexAtPathStart,
                                          charBuffer.begin() + charIndex -
                                              identifierIndex + 1);
                        OverwriteAndInsert(charBuffer,
                                           indexAtPathStart -
                                               TEMPLATE_VALUE_START.size(),
                                           charIndex + 1,
                                           value,
                                           0,
                                           value.size());
                        expecting = WAITING;
                        identifierIndex = 0;
                    }
                }
            default:
                break;
        }
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

} // namespace csp
