//
// Created by popof on 19.04.2018.
//

#ifndef BLACKENGINE_SCENEMANAGER_H
#define BLACKENGINE_SCENEMANAGER_H

#include <core/render/Renderer.h>
#include <core/Copyable.h>
#include <core/render/Object.h>

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
        virtual void addObject(std::shared_ptr<render::Object> object) = 0;
        virtual void addObjects(const render::ObjectList &objectList) = 0;
        virtual void removeObject(std::shared_ptr<render::Object> object) = 0;
        virtual void clear() = 0;

        Scene *copy() const override = 0;

        virtual const render::ObjectList &getObjectList() = 0;
    };
}


#endif //BLACKENGINE_SCENEMANAGER_H
