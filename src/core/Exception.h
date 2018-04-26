//
// Created by popof on 16.04.2018.
//

#ifndef BLACKENGINE2018_EXCEPTION_H
#define BLACKENGINE2018_EXCEPTION_H

#include <string>
#include <utility>
#include <sstream>

namespace black {
    class Exception : std::exception {
    protected:
        std::string message;

    public:
        explicit Exception() : message() {}
        explicit Exception(std::string message) : message(std::move(message)) {}

        const char *what() const noexcept {
            return message.c_str();
        }

        const std::string &getMessage() const {
            return message;
        }
    };

    class FileNotFoundException : public Exception {
    public:
        explicit FileNotFoundException(const std::string &filename) : Exception() {
            std::stringstream ss;
            ss << "File with name '" << filename << "' not found";
            this->message = ss.str();
        }
    };

    class FileFormatUnknownException : public Exception {
    public:
        explicit FileFormatUnknownException(const std::string &format) : Exception() {
            std::stringstream ss;
            ss << "Unknown file format '" << format << "'";
            this->message = ss.str();
        }
    };
}


#endif //BLACKENGINE2018_EXCEPTION_H
