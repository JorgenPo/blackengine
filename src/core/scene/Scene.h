//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_SCENEMANAGER_H
#define BLACKENGINE_SCENEMANAGER_H

#include <core/render/Renderer.h>
#include <core/Copyable.h>
#include <core/GameEntity.h>
#include <core/Camera.h>

namespace black::scene {
    /**
     * Scene arranges renderable object and provide
     * RenderableList of object in render order.
     * Scene allows to add, remove, move objects on scene.
     *
     * Scene is an abstract class. Concrete subclasses provide
     * all logic.
     */
    class Scene : public Copyable {
    public:
        virtual std::string getPrototypeName() = 0;

        virtual std::shared_ptr<Camera> getCurrentCamera() = 0;
        virtual void setCurrentCamera(std::shared_ptr<Camera> camera) = 0;
        virtual void addEntity(std::shared_ptr<Camera> camera) = 0;
        virtual void addEntity(std::shared_ptr<GameEntity> object) = 0;
        virtual void addEntities(const GameEntityList &objectList) = 0;
        virtual void removeEntity(std::shared_ptr<GameEntity> object) = 0;
        virtual void clear() = 0;

        Scene *copy() const override = 0;

        virtual const GameEntityList &getEntityList() = 0;
    };
}


#endif //BLACKENGINE_SCENEMANAGER_H
