//
// Created by popof on 26.09.2018.
//

#include "AbstractSharedLibrary.h"

namespace black {

AbstractSharedLibrary::AbstractSharedLibrary(std::string name) : name(std::move(name)) {}

LibraryNotFoundException::LibraryNotFoundException(std::string name) : Exception() {
  this->message << "Library with name " << name << " not found";
}

FunctionNotFoundException::FunctionNotFoundException(std::string library, std::string function)
    : function(std::move(function)) {
  this->message << "Function " << function << "() not found in " << library;
}

const std::string &FunctionNotFoundException::getFunction() const {
  return function;
}
}