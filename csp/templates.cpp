#include "templates.hpp"

// Standard includes
#include <filesystem>
#include <fstream>
#include <iostream>

namespace csp {

const std::string TEMPLATE_EXTENSION = ".thtml";
const std::string FILE_INCLUDE_START = "{{ ";
const std::string FILE_INCLUDE_END = " }}";
const std::string VALUE_INCLUDE_START = "[[ ";
const std::string VALUE_INCLUDE_END = " ]]";
const bool FILE_INCLUDE = false;
const bool VALUE_INCLUDE = true;

std::string ERR_INVALID_PATH = "Invalid file path";
std::string ERR_INVALID_RANGE = "Invalid range";

std::vector<char> LoadTemplate(const std::string& pathToFile,
                               MatchIncludeValueToVariable matchFunction)
{
    std::vector<char> charBuffer(1);
    std::vector<template_file> templateFiles = {
        { pathToFile, 0, charBuffer.size() }
    };
    templateFiles.reserve(10);

    const int WAITING = 0;
    const int FILE_START = 1;
    const int FILE_END = 2;
    const int VALUE_START = 3;
    const int VALUE_END = 4;

    for (size_t templateFileIndex = 0; templateFileIndex < templateFiles.size();
         templateFileIndex++) {
        template_file& templateFile = templateFiles.at(templateFileIndex);

        std::ifstream fileOnSystem(templateFile.pathToFile);
        if (!fileOnSystem.is_open()) {
            throw std::runtime_error(ERR_INVALID_PATH);
        }

        size_t fileSize = std::filesystem::file_size(templateFile.pathToFile);
        size_t oldCharBufferSize = charBuffer.size();
        size_t deltaIdentifier =
            templateFile.identifierEnd - templateFile.identifierStart;
        charBuffer.resize(charBuffer.size() + fileSize - deltaIdentifier);

        for (size_t i = oldCharBufferSize - 1;
             i >= templateFile.identifierStart + deltaIdentifier;
             i--) {
            charBuffer.at(i + fileSize - deltaIdentifier) = charBuffer.at(i);
        }

        int expecting = WAITING;
        size_t identifierIndex = 0;
        size_t includeStart = 0;

        for (size_t charIndex = templateFile.identifierStart;
             charIndex < templateFile.identifierStart + fileSize;
             charIndex++) {
            charBuffer.at(charIndex) = fileOnSystem.get();
            char& character = charBuffer.at(charIndex);

            switch (expecting) {
            case WAITING:
                if (character == FILE_INCLUDE_START.at(identifierIndex)) {
                    expecting = FILE_START;
                    identifierIndex++;
                } else if (character ==
                           VALUE_INCLUDE_START.at(identifierIndex)) {
                    expecting = VALUE_START;
                    identifierIndex++;
                }
                break;
            case FILE_START:
                if (character != FILE_INCLUDE_START.at(identifierIndex)) {
                    expecting = WAITING;
                    identifierIndex = 0;
                    break;
                }
                if (++identifierIndex != FILE_INCLUDE_START.size()) {
                    break;
                }

                expecting = FILE_END;
                identifierIndex = 0;
                includeStart = charIndex + 1;
                break;
            case FILE_END: {
                if (character != FILE_INCLUDE_END.at(identifierIndex)) {
                    break;
                }
                if (++identifierIndex != FILE_INCLUDE_END.size()) {
                    break;
                }

                std::filesystem::path pathToNewFile(
                    charBuffer.begin() + includeStart,
                    charBuffer.begin() + charIndex + 1 -
                        FILE_INCLUDE_END.size());

                if (pathToNewFile.extension() == TEMPLATE_EXTENSION) {
                    template_file newTemplateFile = {
                        (pathToNewFile),
                        (includeStart - FILE_INCLUDE_START.size()),
                        (charIndex + 1)
                    };
                    templateFiles.push_back(newTemplateFile);
                } else {
                    template_include newFileInclude = {
                        (FILE_INCLUDE),
                        (pathToNewFile),
                        (includeStart - FILE_INCLUDE_START.size()),
                        (charIndex + 1)
                    };
                    templateFile.includes.push_back(newFileInclude);
                }

                expecting = WAITING;
                identifierIndex = 0;
                break;
            }
            case VALUE_START:
                if (character != VALUE_INCLUDE_START.at(identifierIndex)) {
                    expecting = WAITING;
                    identifierIndex = 0;
                    break;
                }
                if (++identifierIndex != VALUE_INCLUDE_START.size()) {
                    break;
                }

                expecting = VALUE_END;
                identifierIndex = 0;
                includeStart = charIndex + 1;
                break;
            case VALUE_END: {
                if (character != VALUE_INCLUDE_END.at(identifierIndex)) {
                    break;
                }
                if (++identifierIndex != VALUE_INCLUDE_END.size()) {
                    break;
                }

                std::string newValue(charBuffer.begin() + includeStart,
                                     charBuffer.begin() + charIndex + 1 -
                                         FILE_INCLUDE_END.size());

                template_include newValueInclude = {
                    (VALUE_INCLUDE),
                    (newValue),
                    (includeStart - VALUE_INCLUDE_START.size()),
                    (charIndex + 1)
                };
                templateFile.includes.push_back(newValueInclude);

                expecting = WAITING;
                identifierIndex = 0;
                break;
            }
            default:
                break;
            }
        }

        fileOnSystem.close();

        ssize_t indexShift = 0;
        ssize_t previousIndexShift = 0;
        for (template_include& fileInclude : templateFile.includes) {
            size_t identifierStartBeforeShift = fileInclude.identifierStart;
            // size_t identifierEndBeforeShift = fileInclude.identifierEnd;
            fileInclude.identifierStart += indexShift;
            fileInclude.identifierEnd += indexShift;

            if (fileInclude.type == FILE_INCLUDE) {
                size_t includeFileSize =
                    std::filesystem::file_size(fileInclude.payload);
                OverwriteAndInsertFile(charBuffer,
                                       fileInclude.identifierStart,
                                       fileInclude.identifierEnd -
                                           fileInclude.identifierStart,
                                       fileInclude.payload,
                                       includeFileSize);

                indexShift += includeFileSize - (fileInclude.identifierEnd -
                                                 fileInclude.identifierStart);
            } else if (fileInclude.type == VALUE_INCLUDE) {
                std::string value(fileInclude.payload.begin(),
                                  fileInclude.payload.end());

                std::string matched = matchFunction(value);
                std::vector<char> conMatched(matched.begin(), matched.end());

                OverwriteAndInsert(charBuffer,
                                   fileInclude.identifierStart,
                                   fileInclude.identifierEnd,
                                   conMatched,
                                   0,
                                   conMatched.size());

                indexShift += conMatched.size() - (fileInclude.identifierEnd -
                                                   fileInclude.identifierStart);
            }

            for (auto nextTemplateFile =
                     templateFiles.begin() + templateFileIndex + 1;
                 nextTemplateFile != templateFiles.end();
                 ++nextTemplateFile) {
                if (nextTemplateFile->identifierStart >
                    identifierStartBeforeShift) {
                    ssize_t deltaIndexShift = indexShift - previousIndexShift;
                    nextTemplateFile->identifierStart += deltaIndexShift;
                    nextTemplateFile->identifierEnd += deltaIndexShift;
                }
            }

            previousIndexShift = indexShift;
        }
    }

    return charBuffer;
}

void OverwriteAndInsert(std::vector<char>& first,
                        size_t firstBegin,
                        size_t firstEnd,
                        std::vector<char>& second,
                        size_t secondBegin,
                        size_t secondEnd)
{
    if (firstBegin > firstEnd || secondBegin > secondEnd) {
        throw std::runtime_error(ERR_INVALID_RANGE);
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

void OverwriteAndInsertFile(std::vector<char>& first,
                            size_t firstBegin,
                            size_t firstOverwriteSize,
                            const std::string& pathToFile,
                            size_t charsToRead)
{
    size_t oldFirstSize = first.size();
    first.resize(first.size() + charsToRead - firstOverwriteSize);

    for (size_t i = oldFirstSize - 1; i >= firstBegin + firstOverwriteSize;
         i--) {
        first.at(i + charsToRead - firstOverwriteSize) = first.at(i);
    }

    std::ifstream file(pathToFile);
    if (!file.is_open()) {
        throw std::runtime_error(ERR_INVALID_RANGE);
    }

    for (size_t i = firstBegin; i < firstBegin + charsToRead; i++) {
        first.at(i) = file.get();
    }
}

} // namespace csp