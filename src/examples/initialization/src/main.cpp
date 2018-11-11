//
// Created by popof on 24.09.2018.
//
#include <iostream>
#include <memory>
#include <Engine.h>
#include <application/GameApplication.h>
#include <util/ModelManager.h>

using namespace black;

class BlackEngineApplication : public GameApplication {
    std::shared_ptr<Model> model;
    glm::mat4 modelMatrix;
    glm::mat4 translation;
    glm::mat4 scale;
    glm::mat4 rotation;

public:
    BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
            800, 600, false), modelMatrix(1.0f) {
        this->translation = glm::mat4(1.0f);
        this->scale = glm::mat4(1.0f);
        this->rotation = glm::mat4(1.0f);
    }

private:
    void update(float dt) override {
        //this->translation = glm::translate(this->translation, glm::vec3(0.0000f, 0.0f, 0.00001f));
        this->scale = glm::scale(this->scale, glm::vec3((1.0f + 0.0001f * dt)));
        this->rotation = glm::rotate(this->rotation, glm::radians(0.01f), glm::vec3(1.0f, 0.2f, 0.0f));

        this->modelMatrix = this->translation * this->rotation * this->scale;

        this->renderer->render(this->model, this->modelMatrix);
    }

    void initializeResources() override {
        //this->model = ModelManager::CreateEquilateralTriangle(0.3f);
        this->model = ModelManager::CreateFromFile("models/models.obj");
        //this->model = ModelManager::CreateFromMesh(fromFile->getPart("Cube").mesh);
    }
};


int main(int argc, char **argv) {
    try {
        BlackEngineApplication application;
        application.start();
    } catch(const std::exception &e) {
        std::cout << "Failed to start application: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}