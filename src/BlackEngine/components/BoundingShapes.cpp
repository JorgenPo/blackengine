//
// Created by popov on 06.07.2019.
//

#include "BoundingShapes.h"
#include "TransformComponent.h"

#include "../tracer/RayTracer.h"
#include "../log/Logger.h"

#include <glm/glm.hpp>
#include <cmath>


std::vector<Point3D> black::Sphere::getIntersectionsWith(const Ray &ray) {
  // http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html
  auto center = transform->getPosition();
  auto L = center - ray.origin;

  // Non uniform scaling doesn't work for sphere
  auto radiusScaled = transform->getScale().x * radius;

  float tc = glm::dot(ray.direction, L);
  if (tc < 0) {
    return {};
  }

  auto lengthOfL = glm::length(L);
  std::vector<Point3D> result;

  auto d = std::sqrt(lengthOfL*lengthOfL - tc * tc);

  if (d > radiusScaled) {
    return result;
  }

  auto t1c = std::sqrt(radiusScaled * radiusScaled - d * d);

  auto p1 = ray.origin + (tc - t1c) * ray.direction;
  auto p2 = ray.origin + (tc + t1c) * ray.direction;

  result.push_back(Point3D{p1.x, p1.y, p1.z});
  if (d < radiusScaled) {
    result.push_back(Point3D{p2.x, p2.y, p2.z});
  }

  return result;
}

black::Sphere::Sphere(std::shared_ptr<TransformComponent> transform, float radius)
  : BoundingShape(std::move(transform)), radius(radius) {

}

black::BoundingShape::BoundingShape(std::shared_ptr<TransformComponent> transform) : transform(std::move(transform)) {}

black::Plane::Plane(std::shared_ptr<TransformComponent> transform, glm::vec3 normal, float fromOrigin)
  : BoundingShape(std::move(transform)), normal(glm::normalize(normal)), distanceFromOrigin(fromOrigin) {

}

std::vector<Point3D> black::Plane::getIntersectionsWith(const black::Ray &ray) {
  auto normal4D = glm::vec4(normal, 0.0f) * transform->getModelMatrix();
  auto normal3D = glm::vec3(normal4D);

  float nominator = -glm::dot(normal3D, ray.origin) + distanceFromOrigin;

  if (nominator == 0) {
    return {};
  }

  float denominator = glm::dot(ray.direction, normal3D);
  float t = nominator / denominator;

  auto intersectionPoint = ray.origin + ray.direction * t;
  return {Point3D{intersectionPoint.x, intersectionPoint.y, intersectionPoint.z}};
}
