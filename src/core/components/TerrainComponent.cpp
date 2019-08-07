//
// Created by popov on 24.07.2019.
//

#include "TerrainComponent.h"

#include <utility>

namespace black {

TerrainComponent::TerrainComponent(std::shared_ptr<ModelComponent> model, HeightMap map)
  : model(std::move(model)),
  heightMap(std::move(map)) {
}

float TerrainComponent::getHeightAt(float width, float height) const {
  return 0.0f;
}

const std::shared_ptr<ModelComponent> &TerrainComponent::getModel() const {
  return model;
}
}