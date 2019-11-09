//
// Created by popov on 24.07.2019.
//

#ifndef BLACKENGINE_TERRAINCOMPONENT_H
#define BLACKENGINE_TERRAINCOMPONENT_H

#include "Component.h"
#include "../common/Exported.h"

#include <memory>
#include <vector>

namespace black {

class ModelComponent;

class BLACK_EXPORTED TerrainComponent : public Component {
public:
  using HeightMap = std::vector<std::vector<float>>;

  static constexpr const char *GetName() { return "TerrainComponent"; }
private:
  std::shared_ptr<ModelComponent> model;
  HeightMap heightMap;

public:
  explicit TerrainComponent(std::shared_ptr<ModelComponent> model, HeightMap heightMap);

  [[nodiscard]] float getHeightAt(float width, float height) const;
  [[nodiscard]] const std::shared_ptr<ModelComponent> &getModel() const;
};

}


#endif //BLACKENGINE_TERRAINCOMPONENT_H
