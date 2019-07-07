//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_BOUNDINGSHAPES_H
#define BLACKENGINE_BOUNDINGSHAPES_H

#include <memory>

namespace black {

class TransformComponent;
class Ray;

/**
 * Bounding shape such as box cylinder and sphere
 */
class BoundingShape {
protected:
  std::shared_ptr<TransformComponent> transform;

public:

  explicit BoundingShape(std::shared_ptr<TransformComponent> transform);

  virtual bool isIntersectsWith(const Ray &ray) = 0;
};

class Sphere : public BoundingShape {
  float radius;

public:
  Sphere(std::shared_ptr<TransformComponent> transform, float radius);

private:
  bool isIntersectsWith(const Ray &ray) override;
};

}


#endif //BLACKENGINE_BOUNDINGSHAPES_H
