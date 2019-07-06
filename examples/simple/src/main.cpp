#include <application/GameApplication.h>

#include <iostream>
#include <memory>

using namespace black;

class BlackEngineApplication : public GameApplication {
  std::vector<std::shared_ptr<GameEntity>> scene;
  std::shared_ptr<Camera> camera;

  float cameraRadius;
  float cameraSpeed;

  bool rotating;
public:
  BlackEngineApplication() : GameApplication(std::string("BlackEngineApplication") + Constants::RuntimePlatformString,
      800, 600, false), cameraRadius(10.0f), cameraSpeed(0.1f), rotating(true) {
  }

private:
  void handleInput() {
    if (Input::IsKeyPressed(Key::KEY_S)) {
      this->cameraRadius += this->cameraSpeed;
    }
    if (Input::IsKeyPressed(Key::KEY_W)) {
      this->cameraRadius -= this->cameraSpeed;
    }

    this->rotating = !Input::IsKeyPressed(Key::KEY_SPACE);
  }

  void update(float dt) override {
    this->handleInput();

    auto time = this->timer->getUptime();

    float camX = static_cast<float>(sin(time / 1000.0)) * this->cameraRadius;
    float camZ = static_cast<float>(cos(time / 1000.0)) * this->cameraRadius;

    if (this->rotating) {
      this->camera->setPosition({camX, 1.3f, camZ});
    }

    this->renderer->render(this->scene, this->camera);
  }

  void initializeResources() override {
    auto cottageModel = ModelManager::CreateFromFile("models/cottage_obj.obj");
    auto cubeModel = ModelManager::CreateFromFile("models/cube.obj");

    auto cottage = std::make_shared<GameEntity>("Cottage");
    cottage->add(cottageModel);
    cottage->transform->scale(0.1f);
    //cottage->transform->scaleZ(2.0f);

    auto cube = std::make_shared<GameEntity>("Cube");
    cube->add(cubeModel);
    cube->transform->scale(1.0f);
    cube->transform->rotateX(35.0f);
    cube->transform->setPosition({3.0f, 0.5f, 3.0f});

    auto car = std::make_shared<GameEntity>("Car");
    car->add(ModelManager::CreateFromFile("models/Shelby.obj"));
    car->transform->setPosition({0.0f, 0.0f, 2.0f});
    car->transform->scale(0.3f);

    auto light = std::make_shared<GameEntity>("Sun");
    light->transform->setPosition({10.0f, 200.0f, 0.0f});
    light->add(std::make_shared<LightComponent>(LightType::DIRECTIONAL));
    light->get<LightComponent>()->setColor(Color{1.0f, 0.8f, 0.8f});

    this->scene.emplace_back(light);
    this->scene.emplace_back(cottage);
    this->scene.emplace_back(cube);
    this->scene.emplace_back(car);

    this->camera = std::make_shared<Camera>(ProjectionType::PERSPECTIVE);
  }
};

int main(int argc, char **argv) {
  try {
    BlackEngineApplication application;
    application.start();
  } catch (const std::exception &e) {
    Logger::Get("Initialization example")->critical("Initialization Example error: ", e.what());
    return 1;
  }

  return 0;
}