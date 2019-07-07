//
// Created by popov on 06.07.2019.
//

#ifndef BLACKENGINE_RAYTRACER_H
#define BLACKENGINE_RAYTRACER_H

#include <glm/vec3.hpp>
#include <memory>

namespace black {

class Camera;

struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;
};

class RayTracer {
  std::shared_ptr<Camera> camera;

public:
  explicit RayTracer(std::shared_ptr<Camera> camera);

  /**
   * Calculate world space unit vector that is a ray from screen coordinates x and y
   * @param x Screen coordinate x
   * @param y Screen coordinate y
   * @return World space unit vector from screen point to the world
   */
  [[nodiscard]] Ray calculateRay(double x, double y) const;

  void setCamera(const std::shared_ptr<Camera> &camera);
};

}

#endif //BLACKENGINE_RAYTRACER_H
