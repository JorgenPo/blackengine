//
// Created by popof on 17.04.2018.
//

#include "SharedLibrary.h"

#include <utility>
#include <sstream>

namespace black {

    SharedLibrary::SharedLibrary(std::string name) : name(std::move(name)) {}

    LibraryNotFoundException::LibraryNotFoundException(std::string name) : Exception() {
        std::ostringstream stream;
        stream << "Library with name " << name << " not found";
        this->message = stream.str();
    }

    FunctionNotFoundException::FunctionNotFoundException(std::string library, std::string function) {
        std::ostringstream stream;
        stream << "Function " << function << "() not found in " << library;
        this->message = stream.str();
    }
}