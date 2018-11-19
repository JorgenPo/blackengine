//
// Created by popof on 24.09.2018.
//
#include <iostream>
#include <memory>
#include <Engine.h>
#include <application/GameApplication.h>
#include <util/ModelManager.h>
#include <util/Input.h>
#include <Camera.h>

using namespace black;

class BlackEngineApplication : public GameApplication {
    std::shared_ptr<Model> model;
    std::shared_ptr<Camera> camera;

    glm::mat4 modelMatrix;
    glm::mat4 translation;
    glm::mat4 scale;
    glm::mat4 rotation;

    float cameraRadius;
    float cameraSpeed;

public:
    BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
            800, 600, false), modelMatrix(1.0f), cameraRadius(10.0f), cameraSpeed(0.1f) {
        this->translation = glm::mat4(1.0f);
        this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f));
        this->rotation = glm::mat4(1.0f);
    }

private:
    void handleInput() {
        if (Input::IsKeyPressed(Key::KEY_S)) {
            this->cameraRadius += this->cameraSpeed;
        }
        if (Input::IsKeyPressed(Key::KEY_W)) {
            this->cameraRadius -= this->cameraSpeed;
        }
    }

    void update(float dt) override {
        //this->translation = glm::translate(this->translation, glm::vec3(0.0000f, 0.0f, 0.00001f));
        this->scale = glm::scale(this->scale, glm::vec3((1.0f + 0.0005f * dt)));
        this->rotation = glm::rotate(this->rotation, glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));

        this->modelMatrix = this->translation * this->rotation * this->scale;

        this->handleInput();

        auto time = this->timer->getUptime();

        float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius;
        float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

        this->camera->setPosition({camX, 1.3f, camZ});

        this->renderer->render(this->model, this->modelMatrix, this->camera);
    }

    void initializeResources() override {
        //this->model = ModelManager::CreateEquilateralTriangle(0.3f);
        this->model = ModelManager::CreateFromFile("models/frog_edited.obj");
        auto frogImage = std::make_shared<Image>("models/frog.jpg", true);
        auto frogTexture = Engine::GetCurrentRenderSystem()->createTexture(frogImage);
        auto material = std::make_shared<Material>(frogTexture);

        this->model->getParts()[0].material = material;

        this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);

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