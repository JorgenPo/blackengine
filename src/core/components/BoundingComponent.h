//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_BOUNDINGCOMPONENT_H
#define BLACKENGINE_BOUNDINGCOMPONENT_H

#include "Component.h"
#include <components/BoundingShapes.h>

#include <memory>

namespace black {

/**
 * Some bounding component
 */
class BoundingComponent : public Component {
  std::shared_ptr<BoundingShape> shape;

public:
  static constexpr const char *GetName() { return "BoundingComponent"; }
  explicit BoundingComponent(std::shared_ptr<BoundingShape> shape);

  [[nodiscard]] const std::shared_ptr<BoundingShape> &getShape() const;
  void setShape(std::shared_ptr<BoundingShape> shape);

  std::vector<Point3D> getIntersectionsWith(const Ray &ray);
};

}


#endif //BLACKENGINE_BOUNDINGCOMPONENT_H
