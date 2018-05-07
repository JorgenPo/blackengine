//
// Created by popof on 19.04.2018.
//

#include "Scene.h"
#include <utility>
#include <core/Core.h>

namespace black::scene {

    EntityCreationException::EntityCreationException(const std::string &name, const std::string &reason) {
        std::stringstream ss;
        ss << "Failed to create an entity with name '" << name << "'. Reason: " << reason;
        this->message = ss.str();
    }

    EntityNotFoundException::EntityNotFoundException(const std::string &name) {
        std::stringstream ss;
        ss << "Entity with name '" << name << "' not found on the scene";
        this->message = ss.str();
    }

    std::shared_ptr<GameEntity> Scene::createEntity(std::string name) {
        auto entity = std::make_shared<GameEntity>(name);
        this->objects.push_back(entity);

        return entity;
    }

    std::shared_ptr<GameEntity> Scene::createEntityWithModel(std::string name, std::string modelFile) {
        auto rm = Core::GetResourceManager();

        try {
            auto model = rm->load<render::Model>(std::move(modelFile));
            auto entity = this->createEntity(name);
            entity->addComponent(model);

            return entity;
        } catch(const Exception &e) {
            throw EntityCreationException(name, e.getMessage());
        }
    }

    std::shared_ptr<GameEntity> Scene::getEntity(std::string name) {
        for (const auto &object : this->objects) {
            if (object->getName() == name) {
                return object;
            }
        }

        return std::shared_ptr<GameEntity>();
    }

    std::shared_ptr<Camera> Scene::createCamera(std::string type, std::string name) {
        try {
            auto camera = Core::getInstance()->createCamera(std::move(type));
            camera->setName(name);

            this->objects.push_back(camera);

            if (this->currentCamera == nullptr) {
                this->currentCamera = camera;
            }

            return camera;
        } catch (const Exception &e) {
            throw EntityCreationException(name, e.getMessage());
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
    Scene::createTerrain(std::string name, std::string terrainTexture, std::string terrainProgram, float width,
                         float height, int levelOfDetails)
    {
        auto rm = Core::GetResourceManager();

        try {
            auto program = rm->load<render::ShaderProgram>(std::move(terrainProgram));
            auto texture = rm->load<render::Texture>(std::move(terrainTexture));

            auto terrain = std::make_shared<Terrain>(texture, program, width, height, levelOfDetails);
            terrain->setName(name);

            this->objects.push_back(terrain);

            return terrain;
        } catch (const Exception &e) {
            throw EntityCreationException(name, e.getMessage());
        }
    }

    std::shared_ptr<Terrain> Scene::getTerrain(std::string name) {
        return std::dynamic_pointer_cast<Terrain>(this->getEntity(std::move(name)));
    }

    std::shared_ptr<render::Sprite>
    Scene::createSprite(std::string name, std::string spriteTexture, std::string spriteProgram) {
        auto rm = Core::GetResourceManager();

        try {
            auto program = rm->load<render::ShaderProgram>(std::move(spriteProgram));
            auto texture = rm->load<render::Texture>(std::move(spriteTexture));

            auto sprite = std::make_shared<render::Sprite>(texture, program);
            sprite->setName(name);

            this->objects.push_back(sprite);

            return sprite;
        } catch (const Exception &e) {
            throw EntityCreationException(name, e.getMessage());
        }
    }

    std::shared_ptr<render::Sprite> Scene::getSprite(std::string name) {
        return std::dynamic_pointer_cast<render::Sprite>(this->getEntity(std::move(name)));
    }

    GameEntityList &Scene::getEntities() {
        return this->objects;
    }
}