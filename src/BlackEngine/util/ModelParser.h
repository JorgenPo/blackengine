//
// Created by popof on 25.04.2018.
//

#ifndef BLACKENGINE_MODELPARSER_H
#define BLACKENGINE_MODELPARSER_H

#include "../common/CommonHeaders.h"

#include "../exceptions/Exception.h"

namespace black {

class ModelComponent;

class ParseException : public Exception {
public:
  explicit ParseException(std::string_view file, std::string_view message)
      : Exception(fmt::format("Failed to parse '{}': {}", file, message)) {
  }
};

class WrongModelFormatException : public Exception {
public:
  explicit WrongModelFormatException() : Exception("Model file is corrupted") {}
};

/**
 * Abstract class for all model parsers
 */
class ModelParser {
public:
  /**
   * Parse model file. After this user can retrieve all model components using
   * appropriate methods.
   * @param file File name containing model to be loaded (parsed).
   *
   * @throws FileNotFoundException If file has not been opened successfully
   */
  virtual void parse(std::string file) = 0;

  /**
   * Is the model parser already parsed the model. Is return is true then user
   * can access model data using appropriate methods.
   *
   * @return Is the model was loaded
   */
  virtual bool isParsed() = 0;

  /**
   * Return the parsed model object. Or nullptr if no model was parsed.
   *
   * @return Parsed model object
   */
  virtual std::shared_ptr<ModelComponent> getModel() = 0;

  /**
   * Return a shared ptr to the model parser of this type
   *
   * @return Model parser of this type
   */
  virtual std::shared_ptr<ModelParser> copy() = 0;
};
}

#endif //BLACKENGINE_MODELPARSER_H
