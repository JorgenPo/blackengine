//
// Created by popov on 09.07.2019.
//

#include "AbstractScene.h"
#include "../Camera.h"

namespace black {

void AbstractScene::setCurrentCamera(std::shared_ptr<Camera> newCamera) {
  currentCamera = std::move(newCamera);
}

std::shared_ptr<Camera> AbstractScene::getCurrentCamera() const {
  return currentCamera;
}

const AmbientLight &AbstractScene::getAmbientLight() const noexcept {
  return ambientLight;
}

void AbstractScene::setAmbientLight(AmbientLight light) {
  ambientLight = light;
}

AbstractScene::~AbstractScene() = default;

}