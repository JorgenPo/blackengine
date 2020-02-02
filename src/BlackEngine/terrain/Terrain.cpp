//
// Created by popov on 21.07.2019.
//

#include "Terrain.h"
#include <BlackEngine/components/ModelComponent.h>
#include <BlackEngine/components/TerrainComponent.h>
#include <BlackEngine/components/BoundingComponent.h>
#include <BlackEngine/components/BoundingShapes.h>

#include <BlackEngine/render/RenderSystemInterface.h>

#include <vector>

namespace black {

const std::shared_ptr<ModelComponent> &Terrain::getModel() const {
  return model;
}

void Terrain::setModel(const std::shared_ptr<ModelComponent> &newModel) {
  model = newModel;
}

const std::shared_ptr<TerrainComponent> &Terrain::getTerrain() const {
  return terrain;
}

void Terrain::setTerrain(const std::shared_ptr<TerrainComponent> &newTerrain) {
  terrain = newTerrain;
}

Terrain::Terrain(std::shared_ptr<ModelComponent> model, std::shared_ptr<TerrainComponent> terrain)
  : GameObject(TERRAIN_OBJECT_NAME), model(std::move(model)), terrain(std::move(terrain)) {
  auto planeShape = std::make_shared<Plane>(transform, glm::vec3{0.0f, 1.0f, 0.0f}, 0.0f);
  bounding = std::make_shared<BoundingComponent>(std::move(planeShape));

  this->add(this->model);
  this->add(this->terrain);
  this->add(this->bounding);
}

const std::shared_ptr<BoundingComponent> &Terrain::getBounding() const {
  return bounding;
}

}