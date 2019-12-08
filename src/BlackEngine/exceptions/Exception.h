//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_EXCEPTION_H
#define BLACKENGINE_EXCEPTION_H

#include "../common/Exported.h"

#include <fmt/format.h>

#include <string>
#include <sstream>
#include <memory>

/**
 * An exception base class and some common exceptions
 */

namespace black {

/**
 * Base class for all Engine exceptions.
 */
class BLACK_EXPORTED Exception : public std::exception, std::enable_shared_from_this<Exception> {
protected:
  // Underlying string stream for better performance
  std::string message;

public:
  Exception(const Exception &another)  : enable_shared_from_this(another), message(another.getMessage()) {
  }

  explicit Exception() : message() {}
  explicit Exception(std::string_view message) : message(message.data()) {
  }

  const char *what() const noexcept override {
    return this->message.c_str();
  }

  /**
   * Returns a message string
   *
   * @return A message string
   */
  const std::string &getMessage() const {
    return message;
  }
};

/**
 * Trying to use an object that has not been initialized yet
 */
class NotInitializedException : public Exception {
public:
  explicit NotInitializedException(std::string_view message) : Exception(message) {}
};

/**
 * File has not been found
 */
class FileNotFoundException : public Exception {
public:
  explicit FileNotFoundException(std::string_view filename)
    : Exception(fmt::format("File with name '{}' not found", filename)) {
  }
};

/**
 * File has an unexpected (unknown) format
 */
class FileFormatUnknownException : public Exception {
public:
  explicit FileFormatUnknownException(std::string_view format)
    : Exception(fmt::format("Unknown file format '{}'", format)) {
  }
};

class NotEnoughDataException : public Exception {
public:
  explicit NotEnoughDataException()  : Exception("Not enough data for operation") {
  }
};

class NotFoundException : public Exception {
public:
  explicit NotFoundException(std::string_view message)  : Exception(message) {
  }
};

class FactoryNotFoundException : public NotFoundException {
public:
  explicit FactoryNotFoundException(std::string_view factoryName)
    : NotFoundException(fmt::format("Factory with a name '{}' not found", factoryName)) {}
};

class FatalError : public Exception {
public:
  explicit FatalError(std::string_view message)
  : Exception(fmt::format("Fatal error: {}", message)) {}
};
}

#endif //BLACKENGINE_EXCEPTION_H

