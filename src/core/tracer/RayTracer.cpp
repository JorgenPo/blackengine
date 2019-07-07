//
// Created by popov on 06.07.2019.
//
#include "RayTracer.h"

#include <Engine.h>
#include <Camera.h>
#include <render/RenderSystemInterface.h>
#include <render/AbstractRenderWindow.h>
#include <log/Logger.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>


namespace black {

RayTracer::RayTracer(std::shared_ptr<Camera> camera) : camera(std::move(camera)) {

}

glm::vec2 getNDCCoordinates(double x, double y) {
  auto window = Engine::GetCurrentRenderSystem()->getRenderWindow();

  return glm::vec2{
    static_cast<float>(2 * x / window->getRenderTargetWidth() - 1),
    -2 * y / window->getRenderTargetHeight() + 1
  };
}

glm::vec4 getEyeCoordinates(const glm::vec4 &clipCoordinates, const std::shared_ptr<Camera> &camera) {
  auto eyeCoords = glm::inverse(camera->getProjectionMatrix()) * clipCoordinates;
  return {eyeCoords.x, eyeCoords.y, -1, 0};
}

glm::vec3 getWorldCoordinates(const glm::vec4 &eyeCoordinates, const std::shared_ptr<Camera> &camera) {
  auto worldCoords = glm::inverse(camera->getViewMatrix()) * eyeCoordinates;
  return {worldCoords.x, worldCoords.y, worldCoords.z};
}

Ray RayTracer::calculateRay(double x, double y) const {
  auto ndcCoordinates = getNDCCoordinates(x, y);
  auto clipCoordinates = glm::vec4(ndcCoordinates.x, ndcCoordinates.y, -1, 1);
  auto eyeCoordinates = getEyeCoordinates(clipCoordinates, camera);
  return {camera->getPosition(), glm::normalize(getWorldCoordinates(eyeCoordinates, camera))};
}

void RayTracer::setCamera(const std::shared_ptr<Camera> &newCamera) {
  camera = newCamera;
}

}