//
// Created by popof on 26.09.2018.
//

#include "AbstractSharedLibrary.h"

namespace black {

AbstractSharedLibrary::AbstractSharedLibrary(std::string name) : name(std::move(name)) {}

LibraryNotFoundException::LibraryNotFoundException(std::string_view name)
  : Exception(fmt::format("Library with name '{}' not found", name)) {
}

FunctionNotFoundException::FunctionNotFoundException(std::string_view library, std::string_view function)
    : Exception(fmt::format("Function '{}' not found in library '{}'", function, library)), function(function) {
}

const std::string &FunctionNotFoundException::getFunction() const {
  return function;
}
}