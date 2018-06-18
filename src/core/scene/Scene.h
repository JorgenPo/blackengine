//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_SCENEMANAGER_H
#define BLACKENGINE_SCENEMANAGER_H

#include <core/render/Renderer.h>
#include <core/Copyable.h>
#include <core/GameEntity.h>
#include <core/Camera.h>
#include <core/Terrain.h>
#include <core/render/Sprite.h>

#include <queue>

namespace black::scene {

    class Scene;

    /**
     * Iterate game entities tree
     */
    class SceneIterator {
        const Scene *scene;
        std::shared_ptr<GameEntity> entity;
        std::queue<std::shared_ptr<GameEntity>> queue;

    public:
        explicit SceneIterator(const Scene *scene, const std::shared_ptr<GameEntity> &entity);

        SceneIterator(const SceneIterator &another);

        virtual ~SceneIterator();

        SceneIterator &operator++();   // Prefix
        const SceneIterator operator++(int); // Postfix
        SceneIterator &operator=(const SceneIterator &iterator);
        std::shared_ptr<GameEntity> &operator*();
        std::shared_ptr<GameEntity> &operator->();

        friend bool operator==(const SceneIterator& first, const SceneIterator& second);
        friend bool operator!=(const SceneIterator& first, const SceneIterator& second);

    private:
        SceneIterator &incrementOperator();
        std::shared_ptr<GameEntity> getNextSiblingOrNull(std::shared_ptr<GameEntity> entity);
    };

    class EntityCreationException : public Exception {
    public:
        explicit EntityCreationException(const std::string &reason);
    };

    class EntityNotFoundException : public Exception {
    public:
        explicit EntityNotFoundException(const std::string &name);
    };

    /**
     * Scene arranges renderable object and provide
     * RenderableList of object in render order.
     * Scene allows to add, remove, move objects on scene.
     *
     * Scene is an abstract class. Concrete subclasses provide
     * all logic.
     */
    class Scene : public Copyable {
        std::shared_ptr<Camera> currentCamera;
        std::shared_ptr<GameEntity> sceneEntity;

    public:
        Scene();

        Scene *copy() const override = 0;

        std::shared_ptr<Camera> createCamera(std::string type);
        void setCurrentCamera(std::string name);
        std::shared_ptr<Camera> getCurrentCamera();
        std::shared_ptr<Camera> getCamera(std::string name);

        std::shared_ptr<GameEntity> createEntity();
        std::shared_ptr<GameEntity> createEntityWithModel(std::string modelFile);
        std::shared_ptr<GameEntity> getEntity(std::string name);

        std::shared_ptr<Terrain> createTerrain(std::string terrainTexture, float width = 200.0f,
                float height = 200.0f, int levelOfDetails = 10);
        std::shared_ptr<Terrain> getTerrain(std::string name);

        std::shared_ptr<render::Sprite> createSprite(std::string spriteTexture);
        std::shared_ptr<render::Sprite> getSprite(std::string name);

        const GameEntityList &getEntities();

        SceneIterator begin() const;
        SceneIterator end() const;
    };
}


#endif //BLACKENGINE_SCENEMANAGER_H
