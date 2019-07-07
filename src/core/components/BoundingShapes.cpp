//
// Created by popov on 06.07.2019.
//

#include "BoundingShapes.h"
#include "TransformComponent.h"

#include <glm/glm.hpp>
#include <cmath>

bool black::Sphere::isIntersectsWith(const glm::vec3 &ray) {
  auto toCenter = glm::vec3{0.0} - center->getPosition();
  float b = glm::dot(ray, toCenter);
  float c = glm::dot(toCenter, toCenter) - radius*radius;

  return b*b - c >= 0;
}

black::Sphere::Sphere(std::shared_ptr<TransformComponent> transform, float radius)
  : BoundingShape(std::move(transform)), radius(radius) {

}

black::BoundingShape::BoundingShape(std::shared_ptr<TransformComponent> center) : center(std::move(center)) {}
