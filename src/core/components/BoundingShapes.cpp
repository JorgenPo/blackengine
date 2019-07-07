//
// Created by popov on 06.07.2019.
//

#include "BoundingShapes.h"
#include "TransformComponent.h"

#include <tracer/RayTracer.h>
#include <log/Logger.h>

#include <glm/glm.hpp>
#include <cmath>


bool black::Sphere::isIntersectsWith(const Ray &ray) {
  // http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
  auto center = transform->getPosition();
  auto L = center - ray.origin;

  // Non uniform scaling doesn't work for sphere
  auto radiusScaled = transform->getScale().x * radius;

  float t = glm::dot(ray.direction, L);
  if (t < 0) {
    return false;
  }

  auto lengthOfL = glm::length(L);
  return std::sqrt(lengthOfL*lengthOfL - t*t) <= radiusScaled;
}

black::Sphere::Sphere(std::shared_ptr<TransformComponent> transform, float radius)
  : BoundingShape(std::move(transform)), radius(radius) {

}

black::BoundingShape::BoundingShape(std::shared_ptr<TransformComponent> transform) : transform(std::move(transform)) {}
