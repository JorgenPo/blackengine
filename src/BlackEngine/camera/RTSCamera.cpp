//
// Created by popov on 08.12.2019.
//

#include "RTSCamera.h"

#include <BlackEngine/GameObject.h>
#include <BlackEngine/input/InputSystemInterface.h>
#include <BlackEngine/log/Logger.h>
#include <BlackEngine/tracer/RayTracer.h>
#include <BlackEngine/scene/AbstractScene.h>
#include <BlackEngine/exceptions/Exception.h>
#include <BlackEngine/terrain/Terrain.h>
#include <BlackEngine/components/TerrainComponent.h>
#include <BlackEngine/components/BoundingComponent.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace black;

void RTSCamera::strafeRight(float value) {
  strafe(getRightVector(), value);
}

void RTSCamera::strafeLeft(float value) {
  strafe(-getRightVector(), value);
}

void RTSCamera::zoomIn(float value) {
  strafe(getLookAt(), value);
}

void RTSCamera::zoomOut(float value) {
  strafe(-getLookAt(), value);
}

void RTSCamera::handleKeyEvents() {
  if (data.input->isKeyPressed(Key::LEFT) || data.input->isKeyPressed(Key::A)) {
    this->strafeLeft(speed);
  }
  if (data.input->isKeyPressed(Key::RIGHT) || data.input->isKeyPressed(Key::D)) {
    this->strafeRight(speed);
  }
  if (data.input->isKeyPressed(Key::UP) || data.input->isKeyPressed(Key::W)) {
    this->strafeTop(speed);
  }
  if (data.input->isKeyPressed(Key::DOWN) || data.input->isKeyPressed(Key::S)) {
    this->strafeBottom(speed);
  }
}

float RTSCamera::getSpeed() const {
  return speed;
}

void RTSCamera::setSpeed(float newSpeed) {
  speed = newSpeed;
}

void RTSCamera::update() noexcept {
  handleKeyEvents();
  handleMouseEvents();
}

void RTSCamera::strafeTop(float value) {
  strafe(getUpVector(), value);
}

void RTSCamera::strafeBottom(float value) {
  strafe(-getUpVector(), value);
}

void RTSCamera::strafe(const glm::vec3 &vector, float value) {
  auto translate = glm::translate(glm::mat4(1.0f), vector * value);
  auto newPosition = translate * glm::vec4{getPosition(), 1.0f};

  setPosition(newPosition);
}

void RTSCamera::handleMouseEvents() {
  if (auto scrollY = data.input->getScrollY(); scrollY != 0) {
    zoomIn(zoomSpeed * scrollY);
  }

  switch (state) {
    case State::NORMAL:
      handleNormalMouseEvents();
      break;
    case State::CAMERA_MOVING:
      handleMovingMouseEvents();
      break;
    case State::CAMERA_ROTATING:
      handleRotatingMouseEvents();
      break;
  }
}

void RTSCamera::onMouseButtonPressed(const MouseButtonEvent &event) {
  anchorPoint = {data.input->getMouseX(), data.input->getMouseY()};

  if (event.button == MouseButton::RIGHT) {
    auto terrainObject = data.scene->getObject(Terrain::TERRAIN_OBJECT_NAME);
    if (terrainObject == nullptr || terrainObject->get<TerrainComponent>() == nullptr) {
      Logger::Get("RTSCamera")->warning(
        "Failed to rotate camera: failed to find a terrain. Terrain is an object with a name '{}'",
        Terrain::TERRAIN_OBJECT_NAME);
      return;
    } else {
      this->terrain = terrainObject->get<BoundingComponent>();
    }

    try {
      calculateTerrainAnchor();
    } catch (const std::exception &e) {
      return;
    }

    rotationStartPosition = getPosition();
    state = State::CAMERA_ROTATING;
  } else if (event.button == MouseButton::LEFT) {
    state = State::CAMERA_MOVING;
  }
}

void RTSCamera::onMouseButtonReleased(const MouseButtonEvent &event) {
  state = State::NORMAL;
}

void RTSCamera::handleNormalMouseEvents() {
  // X strafe
  if ((data.renderTarget->getRenderTargetWidth() - data.input->getMouseX()) < borderWidth) {
    strafeRight(speed);
  } else if (data.input->getMouseX() < borderWidth) {
    strafeLeft(speed);
  }

  if ((data.renderTarget->getRenderTargetHeight() - data.input->getMouseY()) < borderWidth) {
    strafeBottom(speed);
  } else if (data.input->getMouseY() < borderWidth) {
    strafeTop(speed);
  }
}

void RTSCamera::handleRotatingMouseEvents() {
  glm::vec2 currentPosition = {data.input->getMouseX(), data.input->getMouseY()};
  auto difference = anchorPoint - currentPosition;
  auto xDiff = difference.x;

  xDiff = xDiff * speed / 8.0f;

  setPosition({
    rotationStartPosition.x + cos(xDiff) * rotationRadius,
    rotationStartPosition.y,
    rotationStartPosition.x + sin(xDiff) * rotationRadius});
}

void RTSCamera::handleMovingMouseEvents() {
  glm::vec2 currentPosition = {data.input->getMouseX(), data.input->getMouseY()};
  auto difference = anchorPoint - currentPosition;

  difference = difference * speed / 8.0f;
  anchorPoint = currentPosition;
  setPosition(getPosition() + glm::vec3{difference.x, 0.0f, difference.y});
}

RTSCamera::RTSCamera(const CameraData &data) : Camera(data), tracer(nullptr) {

}

void RTSCamera::calculateTerrainAnchor() {
  auto ray = Ray{getPosition(), getLookAt()};
  auto intersections = terrain->getIntersectionsWith(ray);

  if (intersections.empty()) {
    Logger::Get("RTSCamera")->warning("Failed to calculate terrain anchor");
    throw Exception("Failed to calculate terrain anchor");
  }

  terrainAnchorPoint = intersections[0];
}

std::shared_ptr<Camera> RTSCamera::Factory::create(const CameraData &cameraData) const {
  auto data = cameraData;

  data.lookAt = {0.0f, -1.0f, 0.0f};
  auto direction = glm::normalize(data.position - data.lookAt);

  data.up = {0.0f, 0.0f, -1.0f};
  data.right = {1.0f, 0.0f, 0.0f};

  auto camera = std::make_shared<RTSCamera>(std::move(data));
  camera->data.input->subscribeForMouseEvents(camera);
  camera->tracer = std::make_shared<RayTracer>(camera, camera->data.renderTarget);

  return camera;
}
