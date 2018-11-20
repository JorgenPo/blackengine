//
// Created by popof on 19.04.2018.
//

#include "GameEntity.h"
#include <components/TransformComponent.h>

namespace black {

    long long int GameEntity::idCounter = 0;

    GameEntity::GameEntity(std::string name) : name(std::move(name)) {
        if (this->name.empty()) {
            this->name = "Entity" + std::to_string(GameEntity::idCounter);
        }

        this->add(std::make_shared<TransformComponent>());
        this->transform = this->get<TransformComponent>();
    }

    const std::string &GameEntity::getName() const {
        return name;
    }

    void GameEntity::setName(const std::string &name) {
        GameEntity::name = name;
    }

    GameEntity::~GameEntity() = default;
}
