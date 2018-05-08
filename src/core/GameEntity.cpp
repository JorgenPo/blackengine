//
// Created by popof on 19.04.2018.
//

#include <core/components/TransformComponent.h>
#include "GameEntity.h"

namespace black {

    void GameEntity::attachChild(std::shared_ptr<GameEntity> child) {
        this->children.push_back(child);

        if (child->parent != nullptr) {
            child->parent->detachChild(child);
        }

        child->setParent(shared_from_this());
    }

    void GameEntity::detachChild(std::shared_ptr<GameEntity> child) {
        this->children.remove(child);
    }

    GameEntity::GameEntity(std::string name) : name(std::move(name)) {
        this->addComponent(std::make_shared<components::TransformComponent>());
        this->transform = this->getComponent<components::TransformComponent>();
    }

    GameEntity::GameEntity(std::shared_ptr<GameEntity> parent) {

    }

    GameEntity::GameEntity(std::array<float, 3> position) {
        auto transform = std::make_shared<components::TransformComponent>();
        transform->translate({position[0], position[1], position[2]});
        this->addComponent(transform);
    }

    const std::string &GameEntity::getName() const {
        return name;
    }

    void GameEntity::setName(const std::string &name) {
        GameEntity::name = name;
    }

    const std::shared_ptr<GameEntity> &GameEntity::getParent() const {
        return parent;
    }

    void GameEntity::setParent(const std::shared_ptr<GameEntity> &parent) {
        this->parent = parent;
    }

    const GameEntityList &GameEntity::getChildren() const {
        return children;
    }

    GameEntity::~GameEntity() = default;
}
