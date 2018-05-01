#include "SimpleScene.h"

namespace black::scene {
    void SimpleScene::clear() {
        this->objects.clear();
    }

    SimpleScene* SimpleScene::copy() const {
        return new SimpleScene();
    }

    void SimpleScene::addEntity(std::shared_ptr<GameEntity> object) {
        this->objects.push_back(object);
    }

    void SimpleScene::addEntities(const GameEntityList &objectList) {
        this->objects.insert(this->objects.end(), objectList.begin(), objectList.end());
    }

    void SimpleScene::removeEntity(std::shared_ptr<GameEntity> object) {
        this->objects.remove(object);
    }

    const GameEntityList &SimpleScene::getEntityList() {
        return this->objects;
    }

    std::string SimpleScene::getPrototypeName() {
        return this->name;
    }

    std::shared_ptr<Camera> SimpleScene::getCurrentCamera() {
        return this->currentCamera;
    }

    void SimpleScene::setCurrentCamera(std::shared_ptr<Camera> camera) {
        // TODO: check if camera object on scene
        this->currentCamera = camera;
    }

    void SimpleScene::addEntity(std::shared_ptr<Camera> camera) {
        this->objects.push_back(camera);

        if (currentCamera == nullptr) {
            currentCamera = camera;
        }
    }
}
