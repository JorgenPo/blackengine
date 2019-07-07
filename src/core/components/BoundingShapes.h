//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_BOUNDINGSHAPES_H
#define BLACKENGINE_BOUNDINGSHAPES_H

#include <glm/vec3.hpp>

#include <memory>

namespace black {

class TransformComponent;

/**
 * Bounding shape such as box cylinder and sphere
 */
class BoundingShape {
protected:
  std::shared_ptr<TransformComponent> center;

public:

  explicit BoundingShape(std::shared_ptr<TransformComponent> center);

  virtual bool isIntersectsWith(const glm::vec3 &ray) = 0;
};

class Sphere : public BoundingShape {
  float radius;

public:
  Sphere(std::shared_ptr<TransformComponent> transform, float radius);

private:
  bool isIntersectsWith(const glm::vec3 &ray) override;
};

}


#endif //BLACKENGINE_BOUNDINGSHAPES_H
