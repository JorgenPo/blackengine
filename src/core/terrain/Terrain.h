//
// Created by popov on 21.07.2019.
//

#ifndef BLACKENGINE_TERRAIN_H
#define BLACKENGINE_TERRAIN_H

#include <GameObject.h>
#include <memory>

namespace black {

class ModelComponent;
class TerrainComponent;
class BoundingComponent;
class Material;

class BLACK_EXPORTED Terrain : public GameObject {
private:
  std::shared_ptr<ModelComponent> model;
  std::shared_ptr<TerrainComponent> terrain;
  std::shared_ptr<BoundingComponent> bounding;

public:
  Terrain(std::shared_ptr<ModelComponent> model, std::shared_ptr<TerrainComponent> terrain);

  const std::shared_ptr<ModelComponent> &getModel() const;

  void setModel(const std::shared_ptr<ModelComponent> &model);

  const std::shared_ptr<TerrainComponent> &getTerrain() const;

  void setTerrain(const std::shared_ptr<TerrainComponent> &terrain);

  const std::shared_ptr<BoundingComponent> &getBounding() const;
};

}


#endif //BLACKENGINE_TERRAIN_H
