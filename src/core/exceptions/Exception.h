//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_EXCEPTION_H
#define BLACKENGINE_EXCEPTION_H

#include <string>
#include <sstream>
#include <Exported.h>

/**
 * An exception base class and some common exceptions
 */

namespace black {

    /**
     * Base class for all Engine exceptions.
     */
    class BLACK_EXPORTED Exception : std::exception {
    protected:
        // Underlying string stream for better performance
        std::stringstream message;

    public:
        explicit Exception() : message() {}
        explicit Exception(const std::string &message) : message() {
            this->message << message;
        }

        const char *what() const noexcept override {
            return message.str().c_str();
        }

        /**
         * Returns a message string
         *
         * @return A message string
         */
        const std::string getMessage() const {
            return message.str();
        }
    };

    /**
     * Trying to use an object that has not been initialized yet
     */
    class NotInitializedException : public Exception {
    public:
        explicit NotInitializedException(const std::string &message) : Exception(message) {}
    };

    /**
     * File has not been found
     */
    class FileNotFoundException : public Exception {
    public:
        explicit FileNotFoundException(const std::string &filename) : Exception() {
            this->message << "File with name '" << filename << "' not found";
        }
    };

    /**
     * File has an unexpected (unknown) format
     */
    class FileFormatUnknownException : public Exception {
    public:
        explicit FileFormatUnknownException(const std::string &format) : Exception() {
            this->message << "Unknown file format '" << format << "'";
        }
    };
}


#endif //BLACKENGINE_EXCEPTION_H

