//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_BOUNDINGCOMPONENT_H
#define BLACKENGINE_BOUNDINGCOMPONENT_H

#include "Component.h"
#include "BoundingShapes.h"

#include <memory>

namespace black {

/**
 * Some bounding component
 */
class BoundingComponent : public Component {
  std::shared_ptr<BoundingShape> shape;
  bool intersectionEnabled;

public:
  static constexpr const char *GetName() { return "BoundingComponent"; }
  explicit BoundingComponent(std::shared_ptr<BoundingShape> shape);

  [[nodiscard]] const std::shared_ptr<BoundingShape> &getShape() const;
  void setShape(std::shared_ptr<BoundingShape> shape);

  [[nodiscard]] bool isIntersectionEnabled() const;
  void setIntersectionEnabled(bool enableIntersection);

  std::vector<glm::vec3> getIntersectionsWith(const Ray &ray);
};

}


#endif //BLACKENGINE_BOUNDINGCOMPONENT_H
