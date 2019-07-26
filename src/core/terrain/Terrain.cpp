//
// Created by popov on 21.07.2019.
//

#include "Terrain.h"
#include "components/ModelComponent.h"
#include "components/TerrainComponent.h"

#include <Engine.h>
#include <log/Logger.h>
#include <render/RenderSystemInterface.h>
#include <util/ModelManager.h>

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
  : model(std::move(model)), terrain(std::move(terrain)) {
  this->add(this->model);
  this->add(this->terrain);
}

}