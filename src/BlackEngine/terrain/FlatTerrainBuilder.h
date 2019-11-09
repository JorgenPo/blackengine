//
// Created by popov on 25.07.2019.
//

#ifndef BLACKENGINE_FLATTERRAINBUILDER_H
#define BLACKENGINE_FLATTERRAINBUILDER_H

#include "TerrainBuilder.h"

namespace black {

/**
 * FlatTerrainBuilder makes simple flat terrain
 */
class FlatTerrainBuilder : public TerrainBuilder {
public:
  std::shared_ptr<Terrain> build(const Data &data) const override;
};

}


#endif //BLACKENGINE_FLATTERRAINBUILDER_H
