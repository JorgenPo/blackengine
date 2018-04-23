//
// Created by popof on 19.04.2018.
//

#include <core/components/TransformComponent.h>
#include "GameEntity.h"

namespace black {

    void GameEntity::attachChild(std::shared_ptr<GameEntity> child) {
        this->children.push_back(child);
    }

    void GameEntity::detachChild(std::shared_ptr<GameEntity> child) {
        this->children.remove(child);
    }

    GameEntity::GameEntity() {
        this->addComponent("Transform", std::make_shared<components::TransformComponent>());
    }

    GameEntity::GameEntity(std::shared_ptr<GameEntity> parent) {

    }

    GameEntity::GameEntity(std::array<float, 3> position) {
        auto transform = std::make_shared<components::TransformComponent>();
        transform->setPosition(position);
        this->addComponent("Transform", transform);
    }


}
