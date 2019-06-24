//
// Created by popof on 25.10.2018.
//

#ifndef BLACKENGINE_MESHMANAGER_H
#define BLACKENGINE_MESHMANAGER_H

#include <CommonHeaders.h>
#include <exceptions/Exception.h>

#include <unordered_map>
#include <memory>

namespace black {
class ModelParser;
class ModelComponent;
class Mesh;

/**
 * Unknown model format exception
 */
class UnknownFormatException : public Exception {
public:
  explicit UnknownFormatException(std::string extension);
};

/**
 * Mesh helper class. Util functions.
 */
class BLACK_EXPORTED ModelManager {
  static std::unordered_map<std::string, std::shared_ptr<ModelParser>> parsers;

public:
  static std::shared_ptr<ModelComponent> CreateSquare(float sideSize);

  static std::shared_ptr<ModelComponent> CreateEquilateralTriangle(float sideSize);

  static std::shared_ptr<ModelComponent> CreateRectangle(float a, float b);

  /**
   * Creates a model from a given file name.
   *
   * @param fileName Name of a file from which a model could be loaded
   *
   * @return Model object
   *
   * @throws UnknownFormatException If no appropriate model parser was found for this model type
   */
  static std::shared_ptr<ModelComponent> CreateFromFile(std::string fileName);

  /**
   * Creates a model from a single mesh using default material.
   *
   * @param mesh Mesh to be added to model
   * @return Model of the mesh
   */
  static std::shared_ptr<ModelComponent> CreateFromMesh(std::shared_ptr<Mesh> mesh);

  /**
   * Add model parser for a given extension.
   *
   * @param parser Model parser object
   * @param extension Extension of model file that the model parser can parse
   */
  static void AddModelParser(std::string extension, std::shared_ptr<ModelParser> parser);
};

}
#endif //BLACKENGINE_MESHMANAGER_H
