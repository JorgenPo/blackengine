//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_BOUNDINGSHAPES_H
#define BLACKENGINE_BOUNDINGSHAPES_H

#include <common/Vector.h>

#include <memory>
#include <vector>

#include <glm/vec3.hpp>

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

  virtual std::vector<Point3D> getIntersectionsWith(const Ray &ray) = 0;
};

class Sphere : public BoundingShape {
  float radius;

public:
  Sphere(std::shared_ptr<TransformComponent> transform, float radius);

private:
  std::vector<Point3D> getIntersectionsWith(const Ray &ray) override;
};

class Plane : public BoundingShape {
  glm::vec3 normal;
  float distanceFromOrigin;

public:
  Plane(std::shared_ptr<TransformComponent> transform, glm::vec3 normal, float distanceFromOrigin);

  std::vector<Point3D> getIntersectionsWith(const Ray &ray) override;
};

}


#endif //BLACKENGINE_BOUNDINGSHAPES_H
