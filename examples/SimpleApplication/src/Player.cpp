//
// Created by popof on 08.05.2018.
//

#include "Player.h"

Player::Player(const std::string &name, std::shared_ptr<scene::Scene> scene)
        : speed(1.0f), lookAtVector(0.0f, 0.0f, 1.0f), rightVector(1.0f, 0.0f, 0.0f)
{
    auto rm = Core::GetResourceManager();

    try {
        this->entity = scene->createEntityWithModel(MODEL_FILE);
        this->entity->transform->scale(0.5f);
        this->entity->transform->rotateY(-90.0f);
    } catch (const Exception &e) {
        // ...
    }
}

const std::shared_ptr<render::Model> &Player::getModel() const {
    return model;
}


float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    Player::speed = speed;
}

void Player::update() {
    this->handleInput();
}

void Player::handleInput() {
    auto eventWindow = Core::getInstance()->getEventWindow();
    if (eventWindow == nullptr) {
        return;
    }

    if (eventWindow->isKeyPressed(InputKey::KEY_W) || eventWindow->isKeyPressed(InputKey::KEY_UP)) {
        this->moveForward();
    }

    if (eventWindow->isKeyPressed(InputKey::KEY_S) || eventWindow->isKeyPressed(InputKey::KEY_DOWN)) {
        this->moveBackward();
    }

    if (eventWindow->isKeyPressed(InputKey::KEY_A) || eventWindow->isKeyPressed(InputKey::KEY_LEFT)) {
        this->moveLeft();
    }

    if (eventWindow->isKeyPressed(InputKey::KEY_D) || eventWindow->isKeyPressed(InputKey::KEY_RIGHT)) {
        this->moveRight();
    }

    if (eventWindow->isKeyPressed(InputKey::KEY_SPACE)) {
    }
}

void Player::moveForward() {
    auto transform = this->entity->transform;
    transform->setPosition(transform->getPosition() + this->lookAtVector * this->speed);
}

void Player::moveBackward() {
    auto transform = this->entity->transform;
    transform->setPosition(transform->getPosition() - this->lookAtVector * this->speed);
}

void Player::moveLeft() {
    auto transform = this->entity->transform;
    //transform->setPosition(transform->getPosition() + this->rightVector * this->speed);
            transform->rotateY(this->speed);
}

void Player::moveRight() {
    auto transform = this->entity->transform;
    //transform->setPosition(transform->getPosition() - this->rightVector * this->speed);
    transform->rotateY(-this->speed);
}

void Player::setCamera(std::shared_ptr<Camera> camera) {
    this->entity->attachChild(camera);
    camera->transform->setPosition({0.0f, 18.0f, -14.0f});
    camera->transform->rotateX(-40.0f);
}
