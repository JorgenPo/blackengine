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

        ObjectList objects;
    public:

        std::string getPrototypeName() override;

        void clear() override;

        void addObject(std::shared_ptr<render::Object> object) override;

        void addObjects(const render::ObjectList &objectList) override;

        void removeObject(std::shared_ptr<render::Object> object) override;

        const ObjectList &getObjectList() override;

        // Copyable interface
        SimpleScene* copy() const override;
    };
}


#endif //BLACKENGINE_SIMPLESCENE_H
