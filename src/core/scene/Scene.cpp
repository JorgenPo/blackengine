//
// Created by popof on 19.04.2018.
//

#include "Scene.h"
#include <utility>
#include <core/Core.h>

namespace black::scene {

    Scene::Scene() {
        this->sceneEntity = std::make_shared<GameEntity>();
    }

    EntityCreationException::EntityCreationException(const std::string &reason) {
        std::stringstream ss;
        ss << "Failed to create an entity. Reason: " << reason;
        this->message = ss.str();
    }

    EntityNotFoundException::EntityNotFoundException(const std::string &name) {
        std::stringstream ss;
        ss << "Entity with name '" << name << "' not found on the scene";
        this->message = ss.str();
    }

    std::shared_ptr<GameEntity> Scene::createEntity() {
        auto entity = std::make_shared<GameEntity>();
        this->sceneEntity->attachChild(entity);
        return entity;
    }

    std::shared_ptr<GameEntity> Scene::createEntityWithModel(std::string modelFile) {
        auto rm = Core::GetResourceManager();

        try {
            auto model = rm->load<render::Model>(std::move(modelFile));
            auto entity = this->createEntity();
            entity->addComponent(model);

            return entity;
        } catch(const Exception &e) {
            throw EntityCreationException(e.getMessage());
        }
    }

    std::shared_ptr<GameEntity> Scene::getEntity(std::string name) {
        for (const auto &object : this->sceneEntity->getChildren()) {
            if (object->getName() == name) {
                return object;
            }
        }

        return std::shared_ptr<GameEntity>();
    }

    std::shared_ptr<Camera> Scene::createCamera(std::string type) {
        try {
            auto camera = Core::getInstance()->createCamera(std::move(type));

            this->sceneEntity->attachChild(camera);

            if (this->currentCamera == nullptr) {
                this->currentCamera = camera;
            }

            return camera;
        } catch (const Exception &e) {
            throw EntityCreationException(e.getMessage());
        }
    }

    void Scene::setCurrentCamera(std::string name) {
        auto camera = this->getCamera(name);

        if (camera == nullptr) {
            throw EntityNotFoundException(name);
        }

        this->currentCamera = camera;
    }

    std::shared_ptr<Camera> Scene::getCamera(std::string name) {
        return std::dynamic_pointer_cast<Camera>(this->getEntity(std::move(name)));
    }

    std::shared_ptr<Camera> Scene::getCurrentCamera() {
        return this->currentCamera;
    }

    std::shared_ptr<Terrain>
    Scene::createTerrain(std::string terrainTexture, std::string terrainProgram, float width,
                         float height, int levelOfDetails)
    {
        auto rm = Core::GetResourceManager();

        try {
            auto program = rm->load<render::ShaderProgram>(std::move(terrainProgram));
            auto texture = rm->load<render::Texture>(std::move(terrainTexture));

            auto terrain = std::make_shared<Terrain>(texture, program, width, height, levelOfDetails);

            this->sceneEntity->attachChild(terrain);

            return terrain;
        } catch (const Exception &e) {
            throw EntityCreationException(e.getMessage());
        }
    }

    std::shared_ptr<Terrain> Scene::getTerrain(std::string name) {
        return std::dynamic_pointer_cast<Terrain>(this->getEntity(std::move(name)));
    }

    std::shared_ptr<render::Sprite>
    Scene::createSprite(std::string spriteTexture, std::string spriteProgram) {
        auto rm = Core::GetResourceManager();

        try {
            auto program = rm->load<render::ShaderProgram>(std::move(spriteProgram));
            auto texture = rm->load<render::Texture>(std::move(spriteTexture));

            auto sprite = std::make_shared<render::Sprite>(texture, program);

            this->sceneEntity->attachChild(sprite);

            return sprite;
        } catch (const Exception &e) {
            throw EntityCreationException(e.getMessage());
        }
    }

    std::shared_ptr<render::Sprite> Scene::getSprite(std::string name) {
        return std::dynamic_pointer_cast<render::Sprite>(this->getEntity(std::move(name)));
    }

    const GameEntityList &Scene::getEntities() {
        return this->sceneEntity->getChildren();
    }

    // ITERATOR

    SceneIterator Scene::begin() const {
        return SceneIterator(this, this->sceneEntity);
    }

    SceneIterator Scene::end() const {
        return SceneIterator(this, std::shared_ptr<GameEntity>());
    }

    // Scene iterator
    SceneIterator::~SceneIterator() = default;

    SceneIterator::SceneIterator(const SceneIterator &another) {
        this->scene = another.scene;
        this->entity = another.entity;
    }

    SceneIterator::SceneIterator(const Scene *scene, const std::shared_ptr<GameEntity> &entity)
            : scene(scene), entity(entity)
    {
    }

    bool operator==(const SceneIterator &first, const SceneIterator &second) {
        return first.entity == second.entity;
    }

    bool operator!=(const SceneIterator &first, const SceneIterator &second) {
        return first.entity != second.entity;
    }

    std::shared_ptr<GameEntity> &SceneIterator::operator*() {
        return this->entity;
    }

    std::shared_ptr<GameEntity> &SceneIterator::operator->() {
        return this->entity;
    }

    SceneIterator &SceneIterator::operator=(const SceneIterator &iterator) {
        this->entity = iterator.entity;
    }

    SceneIterator &SceneIterator::operator++() {
        return this->incrementOperator();
    }

    const SceneIterator SceneIterator::operator++(int a) {
        SceneIterator iterator = *this;
        this->incrementOperator();
        return iterator;
    }

    SceneIterator &SceneIterator::incrementOperator() {
        // If empty tree - return the end
        if (this->entity->getParent() == nullptr && this->entity->getChildren().empty()) {
            *this = this->scene->end();
            return *this;
        }

        if (!this->entity->getChildren().empty()) {
            for (const auto &child : this->entity->getChildren()) {
                this->queue.push(child);
            }
        }

        if (this->queue.empty()) {
            *this = this->scene->end();
            return *this;
        }

        this->entity = this->queue.front();
        this->queue.pop();

        return *this;
    }

    std::shared_ptr<GameEntity> SceneIterator::getNextSiblingOrNull(std::shared_ptr<GameEntity> entity) {
        auto siblings = entity->getParent()->getChildren();

        bool returnNext = false;
        for (const auto &sibling : siblings) {
            if (sibling == entity) {
                returnNext = true;
                continue;
            }

            if (returnNext) {
                return sibling;
            }
        }

        // No siblings
        return std::shared_ptr<GameEntity>();
    }
}