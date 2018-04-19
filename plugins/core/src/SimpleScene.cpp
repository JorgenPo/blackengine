#include "SimpleScene.h"

namespace black::scene {
    void SimpleScene::clear() {
        this->objects.clear();
    }

    SimpleScene* SimpleScene::copy() const {
        return new SimpleScene();
    }

    void SimpleScene::addObject(std::shared_ptr<render::Object> object) {
        this->objects.push_back(object);
    }

    void SimpleScene::addObjects(const render::ObjectList &objectList) {
        this->objects.insert(this->objects.end(), objectList.begin(), objectList.end());
    }

    void SimpleScene::removeObject(std::shared_ptr<render::Object> object) {
        this->objects.remove(object);
    }

    const ObjectList &SimpleScene::getObjectList() {
        return this->objects;
    }

    std::string SimpleScene::getPrototypeName() {
        return this->name;
    }
}
