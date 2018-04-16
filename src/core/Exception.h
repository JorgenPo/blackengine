//
// Created by popof on 16.04.2018.
//

#ifndef BLACKENGINE2018_EXCEPTION_H
#define BLACKENGINE2018_EXCEPTION_H

#include <string>
#include <utility>

namespace black::core {

    class Exception : std::exception {
    protected:
        std::string message;

    public:
        explicit Exception(std::string message) : message(std::move(message)) {}

        const char *what() const noexcept {
            return message.c_str();
        }

        const std::string &getMessage() const {
            return message;
        }
    };

}


#endif //BLACKENGINE2018_EXCEPTION_H
