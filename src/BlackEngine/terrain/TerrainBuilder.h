//
// Created by popov on 24.07.2019.
//

#ifndef BLACKENGINE_TERRAINBUILDER_H
#define BLACKENGINE_TERRAINBUILDER_H

#include "Terrain.h"

#include "../common/Bounded.h"
#include <BlackEngine/render/Material.h>
#include "../exceptions/Exception.h"

#include <memory>

namespace black {
class BLACK_EXPORTED TerrainBuilder {
public:
  using Lod = Bounded<int, 0, 100>;

  struct Data {
    float width{};
    float height{};
    Lod lod{0}; // Level of details
    std::optional<Material> material;
  };

  /**
   * Trying to build a new terrain object.
   *
   * @throws NotEnoughDataException If not all required parameters have been set
   * @return Terrain game object
   */
  [[nodiscard]] virtual std::shared_ptr<Terrain> build(const Data &data) const = 0;
};

}


#endif //BLACKENGINE_TERRAINBUILDER_H
