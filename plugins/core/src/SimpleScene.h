//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_SIMPLESCENE_H
#define BLACKENGINE_SIMPLESCENE_H

#include <core/scene/Scene.h>

namespace black::scene {
    using namespace render;

    /**
     * Simple scene. Not optimized for concrete case
     */
    class SimpleScene : public Scene {
        const std::string name = "Simple Scene";

        GameEntityList objects;
    public:

        std::string getPrototypeName() override;

        void clear() override;

        void addEntity(std::shared_ptr<GameEntity> object) override;

        void addEntities(const GameEntityList &objectList) override;

        void removeEntity(std::shared_ptr<GameEntity> object) override;

        const GameEntityList &getEntityList() override;

        // Copyable interface
        SimpleScene* copy() const override;
    };
}


#endif //BLACKENGINE_SIMPLESCENE_H
