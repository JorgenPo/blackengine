//
// Created by popof on 08.05.2018.
//

#ifndef BLACKENGINE_PLAYER_H
#define BLACKENGINE_PLAYER_H

#include <core/Core.h>

using namespace black;

class Player {
    static constexpr const char* MODEL_FILE = "geisha.fbx";

    glm::vec3 lookAtVector;
    glm::vec3 rightVector;

    std::shared_ptr<render::Model> model;
    float speed;

    std::shared_ptr<GameEntity> entity;
public:
    explicit Player(const std::string &name, std::shared_ptr<scene::Scene> scene);

    const std::shared_ptr<render::Model> &getModel() const;

    float getSpeed() const;
    void setSpeed(float speed);

    void update();

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    void setCamera(std::shared_ptr<Camera> camera);

private:
    void handleInput();
};


#endif //BLACKENGINE_PLAYER_H
