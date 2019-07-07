//
// Created by popof on 28.10.2018.
//

#ifndef BLACKENGINE_MODEL_H
#define BLACKENGINE_MODEL_H

#include "Component.h"

#include <CommonHeaders.h>
#include <exceptions/Exception.h>
#include <render/Material.h>

#include <vector>

namespace black {

class Mesh;
class ApplicationShader;

class BLACK_EXPORTED ModelPartNotFoundException : public Exception {
public:
  explicit ModelPartNotFoundException(const std::string& partName);
};

/**
 * Part of a model. One mesh and material with a name.
 */
struct BLACK_EXPORTED ModelPart {
  std::string name;
  std::shared_ptr<Mesh> mesh;
  Material material;

  ModelPart(std::string name, std::shared_ptr<Mesh> mesh, const Material &material);

};

/**
 * One or more meshes with some material each
 */
class BLACK_EXPORTED ModelComponent : public Component {
  std::vector<ModelPart> parts;
  std::shared_ptr<ApplicationShader> shader;

public:
  static std::string GetName();

  /**
   * Construct a model from model parts
   */
  explicit ModelComponent(std::vector<ModelPart> parts);

  /**
   * Return a list of the model parts
   *
   * @return List of model parts
   */
  std::vector<ModelPart> &getParts();

  /**
   * Get the model part with a specific name.
   *
   * @param name Name of the model part
   * @return Part of the model corresponding a given name
   * @throws ModelPartNotFoundException If ModelPart with a given name has not been found
   */
  ModelPart &getPart(const std::string& name);

  [[nodiscard]] const std::shared_ptr<ApplicationShader> &getShader() const;

  void setShader(const std::shared_ptr<ApplicationShader> &shader);
};

}
#endif //BLACKENGINE_MODEL_H
