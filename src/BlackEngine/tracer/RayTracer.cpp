//
// Created by popov on 06.07.2019.
//
#include "RayTracer.h"

#include "../Engine.h"
#include "../Camera.h"
#include <BlackEngine/render/RenderSystemInterface.h>
#include <BlackEngine/render/AbstractRenderWindow.h>
#include <BlackEngine/log/Logger.h>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>


namespace black {

RayTracer::RayTracer(std::shared_ptr<Camera> camera, std::shared_ptr<AbstractRenderWindow> window) :
camera(std::move(camera)),
window(std::move(window))
{

}

glm::vec2 getNDCCoordinates(double x, double y, float windowWidth, float windowHeight) {
  return glm::vec2{
    static_cast<float>(2 * x / windowWidth - 1),
    -2 * y / windowHeight + 1
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
  auto ndcCoordinates = getNDCCoordinates(x, y,
    window->getRenderTargetWidth(), window->getRenderTargetHeight());
  auto clipCoordinates = glm::vec4(ndcCoordinates.x, ndcCoordinates.y, -1, 1);
  auto eyeCoordinates = getEyeCoordinates(clipCoordinates, camera);
  return {camera->getPosition(), glm::normalize(getWorldCoordinates(eyeCoordinates, camera))};
}

void RayTracer::setCamera(const std::shared_ptr<Camera> &newCamera) {
  camera = newCamera;
}

}