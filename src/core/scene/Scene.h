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

namespace black::scene {

    class EntityCreationException : public Exception {
    public:
        EntityCreationException(const std::string &name, const std::string &reason);
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
        GameEntityList objects;

    public:
        Scene *copy() const override = 0;

        std::shared_ptr<Camera> createCamera(std::string type, std::string name);
        void setCurrentCamera(std::string name);
        std::shared_ptr<Camera> getCurrentCamera();
        std::shared_ptr<Camera> getCamera(std::string name);

        std::shared_ptr<GameEntity> createEntity(std::string name);
        std::shared_ptr<GameEntity> createEntityWithModel(std::string name, std::string modelFile);
        std::shared_ptr<GameEntity> getEntity(std::string name);

        std::shared_ptr<Terrain> createTerrain(std::string name, std::string terrainTexture, std::string terrainProgram,
                                               float width = 200.0f, float height = 200.0f, int levelOfDetails = 10);
        std::shared_ptr<Terrain> getTerrain(std::string name);

        std::shared_ptr<render::Sprite> createSprite(std::string name, std::string spriteTexture, std::string spriteProgram);
        std::shared_ptr<render::Sprite> getSprite(std::string name);

        GameEntityList &getEntities();
    };
}


#endif //BLACKENGINE_SCENEMANAGER_H
